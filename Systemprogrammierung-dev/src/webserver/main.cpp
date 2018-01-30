#include <webserver/server.h>
#include <string>

using namespace std;

static Server *server;

void sigContHandler(int sig) {

}

void sigTermHandler(int sig) {
	if(sig == SIGTERM) {
		delete server;
		exit(0);
	}	
}



int main(int argc, char *argv[]) {
	if (argc == 3) {
		signal(SIGCONT, sigContHandler);
		signal(SIGTERM, sigTermHandler);
		server = new Server();
		server->startServer(atoi(argv[2]), string(argv[1]));
		return 0;
	}
	return -1;
}
