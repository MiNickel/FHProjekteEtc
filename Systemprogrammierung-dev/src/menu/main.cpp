#include "webserver/menu/webserverMenu.h"
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <signal.h>

static webserverMenu server;

void blockSignals() {
	sigset_t mySet;
	sigemptyset(&mySet);
	sigaddset(&mySet, SIGCHLD);
	sigaddset(&mySet, SIGUSR2);
	sigprocmask(SIG_SETMASK, &mySet, NULL);
}

void unblockSignals() {
	sigset_t mySet;
	sigemptyset(&mySet);
	sigaddset(&mySet, SIGCHLD);
	sigaddset(&mySet, SIGUSR2);
	sigprocmask(SIG_UNBLOCK, &mySet, NULL);
}

void sigChildHandler(int sig) {
	if(sig == SIGCHLD) {
		server.shutDownWebServer();		
	}	
}

void sigUsr2Handler(int sig) {
	if(sig == SIGUSR2) {
		blockSignals();
		int new_socket;
		struct sockaddr_in client;
		
		socklen_t c;
		new_socket = accept(server.getSocket_desc(), (struct sockaddr *) &client, &c);
		if (new_socket >= 0) {
			char buffer[1024];	
			int n;
			if ((n = read(new_socket, buffer, (size_t)1023)) >= 0) {
				buffer[n] = '\0';
				string input = string(buffer);
				if (input.compare(0, 3, "NEW") == 0) {
					server.setNewClient(input.substr(4));
					server.incrementClientCounter();
				} else if (input.compare(0, 3, "DEL") == 0) {
					server.setNewClient(string("               "));
				} else if (input.compare(0, 3, "LOG") == 0) {
					server.addLogMsg(input.substr(4));
				}
			}
		}
		close(new_socket);
		unblockSignals();
	}	
}

int main() {
	signal(SIGCHLD, sigChildHandler);
	signal(SIGUSR2, sigUsr2Handler);
	server = webserverMenu();
	server.startMenu();
    return 0;
}

