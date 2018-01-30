#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

class webserverMenu {
	private:	
		WINDOW * winmenu;
		MENU * menu;
		ITEM ** item;
		WINDOW * winstatus;
		WINDOW * pad;
		string www_path;
		int port;
		int childPID;
		int clientCounter;
		int socket_desc;
		struct sockaddr_in server;
		socklen_t c;
		bool openPort(void);
		
	public:
		webserverMenu();
		void goHomeYourDrunk(void);
		void startMenu(void);
		void startWebServer(void);
		void shutDownWebServer(void);
		void setNewClient(const string &client);
		int getSocket_desc();
		void incrementClientCounter();
		void addLogMsg(const string &msg);
};
