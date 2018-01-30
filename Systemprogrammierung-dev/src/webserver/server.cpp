#include "webserver/server.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sstream> 
#include <vector>
#include <fstream>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <ctime>

using namespace std;
void strmode (mode_t mode, char *str);

Server::Server() {
	c = sizeof(struct sockaddr_in);
}

Server::~Server() {
	cout << "Close Server" << endl;
	close(socket_desc);
}

bool Server::startServer(const int port, const string &www_path) {
	path = www_path;
	
	//int socket(int domain, int type, int protocol)
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); //AF_Inet = IPv4 Protokoll
	if (socket_desc == -1){
		cout << "Fehlerbehandlung" << endl;
		return false;
	}
	server.sin_family = AF_INET;//Adressfamilie(IP)
	server.sin_addr.s_addr = INADDR_ANY; //IP-Adresse
	server.sin_port = htons(port);//Port
	
	if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		cout << "Bind failed" << endl;
		perror("Bind Failed");
		return false;
	} else {
		cout << "Bind done" << endl;
	}
	
	running();
	return true;
}

void Server::running() {
	int new_socket;
	struct sockaddr_in client;
	
	listen(socket_desc, 3); //nachgucken
	while (true) {
		cout << "Waiting for incoming connection..." << endl;
		new_socket = accept(socket_desc, (struct sockaddr *) &client, &c);
		if (new_socket < 0) {
			perror("accept failed");
		} else {
			cout << "Connection accepted" << endl;
			char buffer[1024];
			
			char ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(client.sin_addr), ip, INET_ADDRSTRLEN);
			string msg = string("NEW;") + string(ip);
			sendToGui(msg);
			responseTemperatureGetReqest(new_socket, buffer, 1023);
		}
	}
}

void Server::sendToGui(const string &msg) {
	kill(getppid(), SIGUSR2);
	struct sockaddr_in gui;
	memset(&gui, '0', sizeof(gui));
	gui.sin_family = AF_INET;
	inet_pton(AF_INET, string("127.0.0.1").c_str(), &(gui.sin_addr));
	gui.sin_port = htons(9000);
	
	int desc = socket(AF_INET, SOCK_STREAM, 0); //AF_Inet = IPv4 Protokoll
	if (desc == -1){
		cout << "Fehlerbehandlung" << endl;
	}
	
	if ((connect(desc, (struct sockaddr *)&gui, sizeof(gui))) >= 0) {
		send(desc, msg.c_str(), msg.length(), 0);
	}
	close(desc);
}

void Server::simpleEcho(const int socket, char *buffer, const int length) {
	int n;
	if ( (n = read(socket, buffer, length)) < 0) {
		perror("Error read from socket");
	}else{
		buffer[n] = '\0';
		send(socket, buffer, n, 0);
	}
	close(socket);
}

void Server::detectGetRequest(const int socket, char *buffer, const int length) {
	int n;
	string input = "";
	bool reading = true;
	while (reading) {
		if ( (n = read(socket, buffer, length)) < 0) {
			perror("Error read from socket");
			reading = false;
		}else{
			buffer[n] = '\0';
			input += string(buffer);
			if (input.find("\r\n") < input.length()) {
				reading = false;
				input = input.substr(0, input.find("\r\n"));
				size_t pos = input.find("HTTP/1.1");
				if (input.compare(0, 3, "GET") == 0 && pos < input.length()) {
					string path = getAbsolutePath(input);
					send(socket, path.c_str(), path.length(), 0);
				}
			}
		}
	}
	close(socket);
}

void Server::responseGetReqest(const int socket, char *buffer, const int length) {
	int n;
	string input = "";
	bool reading = true;
	while (reading) {
		if ( (n = read(socket, buffer, length)) < 0) {
			perror("Error read from socket");
			reading = false;
		}else{
			buffer[n] = '\0';
			input += string(buffer);
			if (input.find("\r\n") < input.length()) {
				reading = false;
				input = input.substr(0, input.find("\r\n"));
				size_t pos = input.find("HTTP/1.1");
				if (input.compare(0, 3, "GET") == 0 && pos < input.length()) {
					string path = getAbsolutePath(input);
					path = string("<p>") + path + string("</p>");
					const char *byteData = path.c_str();
					string responserHeader = getHTTPResponseHeader(string("200 OK"), string("text/html"), path.length());
					send(socket, responserHeader.c_str(), responserHeader.length(), 0);
					for (unsigned int i = 0; i < path.length(); i++) {
						send(socket, &byteData[i], 1, 0);
					} 
				}
			}
		}
	}
	close(socket);
}

void Server::sendDataGetReqest(const int socket, char *buffer, int const length) {
	int n;
	string input = "";
	bool reading = true;
	while (reading) {
		if ( (n = read(socket, buffer, length)) < 0) {
			perror("Error read from socket");
			reading = false;
		}else{
			buffer[n] = '\0';
			input += string(buffer);
			if (input.find("\r\n") < input.length()) {
				reading = false;
				input = input.substr(0, input.find("\r\n"));
				size_t pos = input.find("HTTP/1.1");
				if (input.compare(0, 3, "GET") == 0 && pos < input.length()) {
					string path = getAbsolutePath(input);
					size_t endingPos = path.find(".");
					if (endingPos < ULONG_MAX) {
						sendFile(path, socket);
					} else {
						string responserHeader = getHTTPResponseHeader(string("404 Not Found"), string("text/html"),0);
						send(socket, responserHeader.c_str(), responserHeader.length(), 0);
					}
				}
			}
		}
	}
	close(socket);
}

void Server::sendDataAndDirectoryGetReqest(const int socket, char *buffer, int const length) {
	int n;
	string input = "";
	bool reading = true;
	while (reading) {
		if ( (n = read(socket, buffer, length)) < 0) {
			perror("Error read from socket");
			reading = false;
		}else{
			buffer[n] = '\0';
			input += string(buffer);
			if (input.find("\r\n") < input.length()) {
				reading = false;
				input = input.substr(0, input.find("\r\n"));
				size_t pos = input.find("HTTP/1.1");
				if (input.compare(0, 3, "GET") == 0 && pos < input.length()) {
					string path = getAbsolutePath(input);
					size_t endingPos = path.find(".");
					if (endingPos < ULONG_MAX) {
						sendFile(path, socket);
					} else {
						getDirectory(path, socket);
					}
				}
			}
		}
	}
	close(socket);
}

void Server::responseTemperatureGetReqest(const int socket, char *buffer, int const length) {
	int n;
	string input = "";
	bool reading = true;
	while (reading) {
		if ( (n = read(socket, buffer, length)) < 0) {
			perror("Error read from socket");
			reading = false;
		}else{
			buffer[n] = '\0';
			input += string(buffer);
			if (input.find("\r\n") < input.length()) {
				reading = false;
				input = input.substr(0, input.find("\r\n"));
				size_t pos = input.find("HTTP/1.1");
				if (input.compare(0, 3, "GET") == 0 && pos < input.length()) {
					string logmsg = string("LOG;") + getCurrentTime() + string(" (recv) ");
					sendToGui(logmsg + input);
					if (input.find("pid=") < input.length()) {
						string pid = input.substr(input.find("pid=") + 4);
						getDaemonWeatherData(pid.substr(0, pid.find(" ")), socket);
					} else {
						string path = getAbsolutePath(input);
						size_t endingPos = path.find(".");
						if (endingPos < ULONG_MAX) {
							sendFile(path, socket);
						} else {
							getDirectory(path, socket);
						}
					}
				}
			}
		}
	}
	close(socket);
	/*=======!!!ggf wieder einkommentieren!!!=======*/
	//sendToGui(string("DEL;"));
}

string Server::getCurrentTime() {
	time_t curtime;
	struct tm *timeinfo;
	char buffer[80];
	
	time(&curtime);
	timeinfo = localtime(&curtime);
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
	return string(buffer);
}

void Server::getDaemonWeatherData(const string &pid, const int socket) {
	int pidNr = stoi(pid);
	kill((pid_t)pidNr, SIGUSR1);
	/*=======!!!ggf sleep!!!=======*/
	pause();
	sendFile(getAbsolutePath("GET /wetter/database.json"), socket);
}

string Server::getDirectory(const string &filename, const int socket) {
	
	struct dirent* dent;
	DIR* srcdir = opendir(filename.c_str());
	string output;
	bool noIndex = true;
	vector<string> files;
	files.clear();
	
	if (srcdir) {
		while((dent = readdir(srcdir)) != NULL && noIndex){
			if (string(dent->d_name).compare("index.html") == 0) {
				noIndex = false;
				sendFile(filename + string("/index.html"),  socket);
				closedir(srcdir);
				return "";
			}
			struct stat *fileInfos = new struct stat;
			string currentFileName = filename + string("/") + string(dent->d_name);
			stat(currentFileName.c_str(), fileInfos);
			
			files.push_back(statToString(fileInfos, currentFileName, dent->d_name));
			
			delete fileInfos;
		}
		closedir(srcdir);
		sendToGui(string("LOG;") + getCurrentTime() + string(" (send) ") + filename);
		sendDirectory(files, socket);
		
		return output;
	}
	string responserHeader = getHTTPResponseHeader(string("404 Not Found"), "text/html", 0);
	send(socket, responserHeader.c_str(), responserHeader.length(), 0);
	return "";
}

void Server::sendDirectory(const vector<string> &data, const int socket) {
	string html = "<html>";
	for (unsigned int i = 0; i < data.size(); i++) {
		html+= data[i] + "<br />";
	}
	html += "</html>";
	
	string responserHeader = getHTTPResponseHeader(string("200 OK"), "text/html", html.size());
	send(socket, responserHeader.c_str(), responserHeader.length(), 0);
	int n = 0;
	while (html[n] != '\0') {
		send(socket, &html[n], 1, 0);
		n++;
	}
}

void Server::sendFile(const string &path, const int socket) {
	cout << path << endl;
	size_t length = 0;
	string data = getFileBytes(path, length).c_str();
	string contentType = getContentType(path.substr(path.find_last_of(".") + 1));
	cout << path.substr(path.find(".")) << endl;
	
	if (string(data).compare("404") == 0) {
		sendToGui(string("LOG;") + getCurrentTime() + string(" (send) FILE NOT FOUND"));
		string responserHeader = getHTTPResponseHeader(string("404 Not Found"), contentType, 0);
		send(socket, responserHeader.c_str(), responserHeader.length(), 0);
	} else {
		sendToGui(string("LOG;") + getCurrentTime() + string(" (send) ") + path);
		string responserHeader = getHTTPResponseHeader(string("200 OK"), contentType, length);
		send(socket, responserHeader.c_str(), responserHeader.length(), 0);
		
		int n = 0;
		while (data[n] != '\0') {
			send(socket, &data[n], 1, 0);
			n++;
		}
	}
}

string Server::getFileBytes(const string &filename, size_t &length) {
	ifstream infile(filename.c_str(), ios_base::binary);
	
	infile.seekg(0, ios_base::end);
	length = infile.tellg();
	infile.seekg(0, infile.beg);
	if (length < ULONG_MAX) {
		int n = length + 1;
		char *data = new char[n];
		
		if (length > 0) { 
			infile.read(data, length);
		}
		data[length] = '\0';
		string dataString = string(data);
		delete[] data;
		return dataString;
	} else {
		char data[4];
		data[0] = '4';
		data[1] = '0';
		data[2] = '4';
		data[3] = '\0';
		return string(data);
	}
}

string Server::getContentType(const string &ending){
	cout << ending.compare("html") << endl;
	if (ending.compare("html") == 0) {
		return string("text/html");
	} else if ((ending.compare("txt") * ending.compare("h") * ending.compare("c") * ending.compare("c++")) == 0) {
		return string("text/plain");
	} else if (ending.compare("pdf") == 0) {
		return string("application/pdf");
	} else if (ending.compare("png") == 0) {
		return string("image/png");
	} else if (ending.compare("jpg") == 0) {
		return string("image/jpeg");
	} else if (ending.compare("css") == 0) {
		return string("text/css");
	} else if (ending.compare("json") == 0) {
		return string("application/json");
	} else {
		return string("application/octet-stream");
	}
}

string Server::getHTTPResponseHeader(const string &statuscode, const string &requestType, const size_t numBytes) {
	stringstream ss;
	ss << (int)numBytes;
	string num = ss.str();
	return string("HTTP/1.1 ") + statuscode + string("\r\n") +
			string("Connection: close\r\n") +
			string("Content-Language: de\r\n") +
			string("Content-Length: ") + num +  string("\r\n") +
			string("Content-Type: ") + requestType + string("\r\n\r\n");
}

string Server::getAbsolutePath(const string &getRequest) {
	string resource = getRequest.substr(4);
	resource = resource.substr(0, resource.find(" "));
	string root = path;
	root += resource;
	
	char *realp = (char  *)malloc(480 * sizeof(char));
	
	realpath(root.c_str(), realp);
	root = string(realp);
	
	free(realp);
	return root;
}

string Server::statToString(const struct stat* file, const string &path, const string &filename) {
	char mode[10];
	stringstream stream;
	
	struct passwd *pwd;
	pwd = getpwuid(file->st_uid);
	string relativePath = path.substr(getAbsolutePath("get ").length());
	
	char buffer;
	strmode(file->st_mode, mode);
	stream >> std::noskipws;
	
	stream << mode << " " << file->st_nlink << " " << pwd->pw_name << " " << file->st_size << " " << ctime (&(file->st_mtime)) << " " << filename ;
	string infos = "<a href=\"" + relativePath + "\">";
	stream >> noskipws;
	
	while (stream >> buffer){
		infos += buffer;
	}
	infos += "</a>";
	return infos;
}

void strmode(mode_t mode, char * buf) {
  
  const char chars[] = "drwxrwxrwx";
  buf[0] = S_ISDIR(mode)? 'd' : '-';
  for (size_t i = 1; i < 10; i++) {
    buf[i] = (mode & (1 << (8-i))) ? chars[i] : '-';
  }
  buf[9] = '\0';
}
