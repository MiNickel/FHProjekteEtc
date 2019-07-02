#pragma once

namespace cg
{
	class AbstractSphere
	{
	public:
		AbstractSphere() : renderNormals(false)
		{
		}

		virtual ~AbstractSphere()
		{
		}

		virtual void render(const glm::mat4& view, const glm::mat4& projection) = 0;
		virtual void setLightVector(const glm::vec4& v) = 0;

		glm::mat4& getModel()
		{
			return model;
		}

		void setModel(glm::mat4& a_model)
		{
			model = a_model;
		}

		void setRenderNormals(bool renderNormals)
		{
			this->renderNormals = renderNormals;
		}

		void toggleRenderNormals()
		{
			renderNormals = !renderNormals;
		}

		bool isRenderNormals() const
		{
			return renderNormals;
		}
	protected:
		bool renderNormals;
	public:
		glm::mat4 model;
	};
}
