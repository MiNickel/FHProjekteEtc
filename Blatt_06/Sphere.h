#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLSLProgram.h"
#include "GLTools.h"
#include "Object.h"
#include "AbstractSphere.h"
 
using namespace std;

namespace cg
{
	class Sphere : public AbstractSphere
	{
	public:
		GLSLProgram programShaded;
		GLSLProgram programSimple;
	private:

		Object objSphere;
		Object objNormals;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> colors;
		std::vector<GLuint> indices;
		std::vector<glm::vec3> normals;
		double m_dRadius;
		bool m_bGouraud;

	public:
		Sphere(const glm::vec3& color, double a_dRadius, GLSLProgram *shader1, GLSLProgram *shader2, bool bGouraud = true)
		{
			m_bGouraud = bGouraud;
			m_dRadius = a_dRadius;
			 initShader();
			 //-AprogramShaded = *shader1;
			//-AprogramSimple = *shader2;
			initObject(color);
		}

		void initShader()
		{
			initShader(programSimple, "shader/simple.vert", "shader/simple.frag");

			if (m_bGouraud)
			{
				initShader(programShaded, "shader/shadedGouraud.vert", "shader/shadedGouraud.frag");

				programShaded.use();
				programShaded.setUniform("light", glm::vec3(0, 0, 0));
				programShaded.setUniform("lightI", float(1.0f));
				programShaded.setUniform("surfShininess", float(8.0f));
				// vec3 ambient = ambientStrength * light; // nach Phong 
				programShaded.setUniform("surfKa", (float(8.0f)*glm::vec3(0, 0, 0)));
				//programShaded.setUniform("surfKa", glm::vec3(0.1f, 0.1f, 0.1f));
				programShaded.setUniform("surfKd", glm::vec3(0.7f, 0.1f, 0.1f));
				programShaded.setUniform("surfKs", glm::vec3(1, 1, 1));
			}
			else
			{
				initShader(programShaded, "shader/shadedPhong.vert", "shader/shadedPhong.frag");
				programShaded.use();
				programShaded.setUniform("light", glm::vec3(0, 0, 0));
				programShaded.setUniform("lightI", float(1.0f));
				programShaded.setUniform("surfKa", glm::vec3(0.1f, 0.1f, 0.1f));
				programShaded.setUniform("surfKd", glm::vec3(0.7f, 0.1f, 0.1f));
				programShaded.setUniform("surfKs", glm::vec3(1, 1, 1));
				programShaded.setUniform("surfShininess", float(8.0f));
			}
		}

		void initBaseSphere()
		{
			vertices = {	// Punkte der Dreiecke
				{ 0.5f, 0.0f, -0.5f }, //front
				{ 0.5f, 0.0f,  0.5f },
				{ 0.0f, 0.87f, 0.0f },

				{ -0.5f, 0.0f, 0.5f },
				{ -0.5f, 0.0f, -0.5f },
				{ 0.0f, -0.87f, 0.0f }
			};

			for (int iCount = 0; iCount < 24; iCount++)
				colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

			// Die Indizes der Punkte, von vorne beginnend
			indices = {
				0, 1, 2,
				2, 1, 3,
				2, 3, 4,
				2, 4, 0,
				5, 4, 0,
				5, 1, 0,
				5, 1, 3,
				5, 3, 4
			};
		}

		// Ist schon ein Punkt in einer aktuellen Liste enthalten
		bool IsVertexSaved(glm::vec3 a_Pnt, int *a_Index)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				double dVert_X = ceilf(vertices.at(i).x * 1000) / 1000;
				double dVert_Y = ceilf(vertices.at(i).y * 1000) / 1000;
				double dVert_Z = ceilf(vertices.at(i).z * 1000) / 1000;

				double dPnt_X = ceilf(a_Pnt.x * 1000) / 1000;
				double dPnt_Y = ceilf(a_Pnt.y * 1000) / 1000;
				double dPnt_Z = ceilf(a_Pnt.z * 1000) / 1000;

				if (dVert_X == dPnt_X &&
					dVert_Y == dPnt_Y &&
					dVert_Z == dPnt_Z)
				{
					*a_Index = i;
					return true;
				}
			}

			return false;
		}

		// Mittelpunkt von 2 Eckpunkten finden
		// HINWEIS: Die Grˆﬂe des neuen Scheitelpunkts muss ge‰ndert werden, damit die L‰nge dem Radius entspricht
		void computeHalfVertex(glm::vec3 v1, glm::vec3 v2, glm::vec3 *newV)
		{
			newV->x = v1[0] + v2[0];    // x
			newV->y = v1[1] + v2[1];    // y
			newV->z = v1[2] + v2[2];    // z
			double dResult = sqrt(newV->x * newV->x + newV->y * newV->y + newV->z * newV->z);
			const double scale = m_dRadius / dResult;
			newV->x = newV->x * (float)scale;
			newV->y = newV->y * (float)scale;
			newV->z = newV->z * (float)scale;
		}

		// Der Unterteilungsalgorithmus teilt die drei Kantenlinien jedes Dreiecks in zwei H‰lften und 
		// extrudiert dann den neuen Mittelpunkt nach auﬂen, sodass seine L‰nge(der Abstand vom Mittelpunkt)
		// dem Radius der Kugel entspricht.
		int SubDivisionAlgorithm(const glm::vec3& a_Color)
		{
			for (int iSubdivision = 1, LoopCount = 2; iSubdivision <= LoopCount; iSubdivision++)
			{
				vector<glm::vec3>tmpColors, tmpNormals, tmpVertices;
				vector<GLushort> tmpIndices;
				glm::vec3 newV1, newV2, newV3; // new vertex positions

				// copy prev vertex/index arrays and clear
				for (int i = 0; i < vertices.size(); i++)
					tmpVertices.push_back(vertices.at(i));

				for (int i = 0; i < indices.size(); i++)
					tmpIndices.push_back(indices.at(i));

				for (int i = 0; i < colors.size(); i++)
					tmpColors.push_back(colors.at(i));

				for (int i = 0; i < normals.size(); i++)
					tmpNormals.push_back(normals.at(i));

				// Aktuelle Daten lˆschen
				vertices.clear();
				indices.clear();
				colors.clear();
				normals.clear();

				// perform subdivision for each triangle
				for (int j = 0, index = 0; j < tmpIndices.size() && (index < 193); j += 3)
				{
					// get 3 vertices of a triangle
					glm::vec3 v1 = tmpVertices[tmpIndices[j]];
					glm::vec3 v2 = tmpVertices[tmpIndices[j + 1]];
					glm::vec3 v3 = tmpVertices[tmpIndices[j + 2]];

					//  3 neue Eckpunkte berechnen, indem die H‰lfte an jeder Kante geteilt wird
					//         v1       
					//        / \       
					// newV1 *---* newV3
					//      / \ / \     
					//    v2---*---v3   
					//       newV2  

					glm::vec3 newV1, newV2, newV3;

					computeHalfVertex(v1, v2, &newV1);
					computeHalfVertex(v2, v3, &newV2);
					computeHalfVertex(v1, v3, &newV3);

					int iIndex_0 = index;
					int iIndex_1 = index + 1;
					int iIndex_2 = index + 2;
					int iIndex_3 = index + 3;
					int iIndex_4 = index + 4;
					int iIndex_5 = index + 5;

					// add 4 new triangles to vertex array
					if (IsVertexSaved(v1, &iIndex_0) == false)
					{
						vertices.push_back(v1);		// #0
						iIndex_0 = (int)vertices.size() - 1;
						normals.push_back(glm::normalize(v1));
					}

					if (IsVertexSaved(v2, &iIndex_1) == false)
					{
						vertices.push_back(v2);		// #1
						iIndex_1 = (int)vertices.size() - 1;
						normals.push_back(glm::normalize(v2));
					}

					if (IsVertexSaved(v3, &iIndex_2) == false)
					{
						vertices.push_back(v3);		// #2
						iIndex_2 = (int)vertices.size() - 1;
						normals.push_back(glm::normalize(v3));
					}

					if (IsVertexSaved(newV1, &iIndex_3) == false)
					{
						vertices.push_back(newV1);	// #3
						iIndex_3 = (int)vertices.size() - 1;
						normals.push_back(glm::normalize(newV1));
					}

					if (IsVertexSaved(newV2, &iIndex_4) == false)
					{
						vertices.push_back(newV2);	// #4
						iIndex_4 = (int)vertices.size() - 1;
						normals.push_back(glm::normalize(newV2));
					}

					if (IsVertexSaved(newV3, &iIndex_5) == false)
					{
						vertices.push_back(newV3);	// #6
						iIndex_5 = (int)vertices.size() - 1;
						normals.push_back(glm::normalize(newV3));
					}

					// Vektoren normalisieren!
					for (int i = 0; i < vertices.size(); i++)
					{
						float x = vertices.at(i).x;
						float y = vertices.at(i).y;
						float z = vertices.at(i).z;
						vertices.at(i) *= 1.0f / sqrt(x*x + y*y + z*z);
					}

					////////////////  indices   ////////////////
					indices.push_back(GLushort(iIndex_0));
					indices.push_back(GLushort(iIndex_3));
					indices.push_back(GLushort(iIndex_5));

					indices.push_back(GLushort(iIndex_3));
					indices.push_back(GLushort(iIndex_1));
					indices.push_back(GLushort(iIndex_4));

					indices.push_back(GLushort(iIndex_3));
					indices.push_back(GLushort(iIndex_4));
					indices.push_back(GLushort(iIndex_5));

					indices.push_back(GLushort(iIndex_5));
					indices.push_back(GLushort(iIndex_4));
					indices.push_back(GLushort(iIndex_2));

					//////////////   colors   //////////////////////////
					for (int iCount = 0; iCount< 12; iCount++)
						colors.push_back(a_Color);

					index += 6;
				}
			}

			return 0;
		}

		void initObject(const glm::vec3& color)
		{
			initBaseSphere();
			SubDivisionAlgorithm(color);

			for (int iCount = 0; iCount < vertices.size(); iCount++)
				normals.push_back(glm::normalize(vertices.at(iCount)));

			GLuint programId = programShaded.getHandle();
			GLuint pos;

			// Vertex array object.
			glGenVertexArrays(1, &objSphere.vao);
			glBindVertexArray(objSphere.vao);

			// Position buffer.
			glGenBuffers(1, &objSphere.positionBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objSphere.positionBuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "position");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Color buffer.
			glGenBuffers(1, &objSphere.colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objSphere.colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "color");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Normal buffer.
			glGenBuffers(1, &objSphere.normalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objSphere.normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "normal");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Index buffer.
			objSphere.indexCount = (GLuint)indices.size();

			glGenBuffers(1, &objSphere.indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexCount * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

			// Build the normals.
			programId = programSimple.getHandle();

			std::vector<glm::vec3> positions2;
			std::vector<glm::vec3> colors2;
			std::vector<GLuint> indices2;

			const glm::vec3 colorNormal(1.0f, 1.0f, 1.0f);
			
			// create vertex-array-object for normal lines
			for (int iCount = 0; iCount < vertices.size(); iCount++)
				addNormal(positions2, colors2, colorNormal, vertices.at(iCount), normals.at(iCount));

			for (GLushort i = 0; i < positions2.size(); i++)
				indices2.push_back(i);
		
			// Vertex array object.
			glGenVertexArrays(1, &objNormals.vao);
			glBindVertexArray(objNormals.vao);

			// Position buffer.
			glGenBuffers(1, &objNormals.positionBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objNormals.positionBuffer);
			glBufferData(GL_ARRAY_BUFFER, positions2.size() * sizeof(glm::vec3), positions2.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "position");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Color buffer.
			glGenBuffers(1, &objNormals.colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objNormals.colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, colors2.size() * sizeof(glm::vec3), colors2.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "color");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);
			
			// Index buffer.
			objNormals.indexCount = (GLuint)indices2.size();

			glGenBuffers(1, &objNormals.indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, objNormals.indexCount * sizeof(GLuint), indices2.data(), GL_STATIC_DRAW);
		
			model = glm::scale(glm::mat4(1.0f), glm::vec3(m_dRadius, m_dRadius, m_dRadius));
		}

		~Sphere()
		{
			// GLSL Programs and objects will be automatically released upon object destruction.
		}

		void render(const glm::mat4& view, const glm::mat4& projection)
		{
 		    glm::mat4 mv  = view * model;
			// Create mvp.
			glm::mat4 mvp = projection * mv;

			// Create normal matrix (nm) from model matrix.
			glm::mat3 nm = glm::inverseTranspose(glm::mat3(model));

			//-A
			// Bind the shader program and set uniform(s).
			/**/programShaded.use();
			programShaded.setUniform("modelviewMatrix",  mv);
			programShaded.setUniform("projectionMatrix", projection);
			programShaded.setUniform("normalMatrix", nm);
			
			// Bind vertex array object so we can render the triangle.
			glBindVertexArray(objSphere.vao);
			glDrawElements(GL_TRIANGLES, objSphere.indexCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			if (renderNormals)
			{
				//-A
				// Bind the shader program and set uniform(s).
				/**/programSimple.use();
				programSimple.setUniform("mvp", mvp);

				// Bind vertex array object so we can render the triangle.
				glBindVertexArray(objNormals.vao);
				glDrawElements(GL_LINES, objNormals.indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
		}
		
		//-A
		void setLightVector (const glm::vec4& v)
		{
			/**/programShaded.use();
			programShaded.setUniform("light", v);
		}
	private:
		static void addNormal(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& colors, const glm::vec3& color, const glm::vec3& vertex, const glm::vec3& normal, float scale = 0.2f)
		{
			positions.push_back(vertex);
			positions.push_back(vertex + normal * scale);
			
			colors.push_back(color);
			colors.push_back(color);
		}

		/**/static void initShader(GLSLProgram& program, const std::string& vert, const std::string& frag)
		{
			if (!program.compileShaderFromFile(vert.c_str(), cg::GLSLShader::VERTEX))
			{
				throw std::runtime_error("COMPILE VERTEX: " + program.log());
			}

			if (!program.compileShaderFromFile(frag.c_str(), cg::GLSLShader::FRAGMENT))
			{
				throw std::runtime_error("COMPILE FRAGMENT: " + program.log());
			}

			if (!program.link())
			{
				throw std::runtime_error("LINK: " + program.log());
			}
		}
	};
}
