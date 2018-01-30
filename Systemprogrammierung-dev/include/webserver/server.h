#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <signal.h>

using namespace std;

class Server {

public:
	Server();
	~Server();
	bool startServer(const int port, const string &www_path);
	void simpleEcho(const int socket, char *buffer, const int length);
	void detectGetRequest(const int socket, char *buffer, const int length);
	void responseGetReqest(const int socket, char *buffer, const int length);
	void sendDataGetReqest(const int socket, char *buffer, const int length);
	void sendDataAndDirectoryGetReqest(const int socket, char *buffer, const int length);
	void responseTemperatureGetReqest(const int socket, char *buffer, const int length);
	
	void sendDirectory(const vector<string> &data, const int socket);
	void sendFile(const string &path, const int socket);
	string getDirectory(const string &filename, const int socket);
	string getFileBytes(const string &filename, size_t &length);
	string getContentType(const string &ending); 
	string getHTTPResponseHeader(const string &statuscode, const string &requestType, const size_t numBytes);
	string getAbsolutePath(const string &getRequest);
	string statToString(const struct stat* file, const string &path, const string &filename);
	void getDaemonWeatherData(const string &pid, const int socket);
	void sendToGui(const string &msg);
	
private:
	void running();
	string path;
	int socket_desc;
	struct sockaddr_in server;
	socklen_t c;
	string getCurrentTime();
};
