#include "webserver/menu/webserverMenu.h"

webserverMenu::webserverMenu() {
	port = 8999;
	www_path = "../../server";
	childPID = -1;
	clientCounter = 0;
}


void webserverMenu::startMenu() {
	openPort();
	initscr();
    clear();
    noecho();
    curs_set(0);
    cbreak();
    nl();
    keypad(stdscr, true);
    start_color();

    //MAIN WINDOW
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));
    border(ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);

    attron(A_BOLD);
    mvprintw(1, COLS/2-8, "Mister Webserver");

    //MENU WINDOW
    winmenu = newwin(8, COLS/3 + 2, 4, 4);
    wborder(winmenu, 0, 0, 0, 0, 0, 0, 0, 0);
    wbkgd(winmenu, COLOR_PAIR(1));

    mvwprintw(winmenu, 1, 4, "*Buttons der Macht*");
	
	item = (ITEM **) calloc(4, sizeof(ITEM *));
	item[0] = new_item("M1", "Start Server");
	item[1] = new_item("M2", "Shutdown Server");
	item[2] = new_item("M3", "Quit");
	
	menu = new_menu(item);
	
	set_menu_mark(menu, "--> ");
	set_menu_win(menu, winmenu);
	set_menu_sub(menu, subwin(winmenu, 3, 0, 7, 5));
	set_menu_fore(menu, COLOR_PAIR(1)|A_REVERSE);
	set_menu_back(menu, COLOR_PAIR(1));

    //STATUS WINDOW
    winstatus = newwin(8, COLS/3 + 12, 4, COLS/2-2);
    wborder(winstatus, 0, 0, 0, 0, 0, 0, 0, 0);
    wbkgd(winstatus, COLOR_PAIR(1));

    mvwprintw(winstatus, 1, 10, "*Staatsgeheimnisse*");

    mvwprintw(winstatus, 3, 2, (string("Server IP: 127.0.0.1:") + to_string(port)).c_str());
    mvwprintw(winstatus, 4, 2, "Server Online: false");
    mvwprintw(winstatus, 5, 2, "Client: ");
    mvwprintw(winstatus, 6, 2, "Connection No.: 0");

    //PAD
    attroff(A_BOLD);
    mvprintw(14, 2, "*** Request Log ***");

	pad = newpad(1000, 200);
	wbkgd(pad, COLOR_PAIR(1));
	
    //ENDE
    refresh();
    post_menu(menu);
	wrefresh(winmenu);
    wrefresh(winstatus);
	prefresh(pad, 0, 0, 16, 2, LINES - 3, COLS - 2);
	
	int ch;
	while((ch = getch()) != KEY_F(1)) {
		switch(ch) {
			case KEY_DOWN:
				menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case 0xA:
				if(item_index(current_item(menu)) == 0) {
					startWebServer();
				} else if(item_index(current_item(menu)) == 1) {
					shutDownWebServer();
				} else if(item_index(current_item(menu)) == 2) {
					goHomeYourDrunk();
					exit(0);
				} 
			}
			wrefresh(winmenu);
	}
}

bool webserverMenu::openPort() {
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); //AF_Inet = IPv4 Protokoll
	if (socket_desc == -1){
		return false;
	}
	server.sin_family = AF_INET;//Adressfamilie(IP)
	server.sin_addr.s_addr = INADDR_ANY; //IP-Adresse
	server.sin_port = htons(9000);//Port
	
	if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("Bind Failed");
		return false;
	}
	
	listen(socket_desc, 3);
	
	return true;
}

void webserverMenu::startWebServer() {
	if (childPID <= 0) {
		pid_t pid = fork();
		if(pid == (pid_t)0) {
			char p[8];
			sprintf(p, "%d", port);
			char w[128];
			strcpy(w, www_path.c_str());
			char *argv[4] = {(char *)"fbtHttpd", w, p, '\0'};
			for (int i = 0; i < sysconf(_SC_OPEN_MAX); i++) {
				close(i);
			}
			open("/dev/null", O_RDWR);
			dup2(STDIN_FILENO, STDOUT_FILENO);
			dup2(STDIN_FILENO, STDERR_FILENO);
					
			execve("../webserver/fbtHttpd", argv, NULL);
			
		}else if (pid > (pid_t)0) {
			childPID = pid;
			mvwprintw(winstatus, 4, 2, "Server Online: true ");
			wrefresh(winstatus);
		}
	}
}

void webserverMenu::shutDownWebServer() {
	if (childPID > 0) {
		kill(childPID, SIGTERM);
		int l = 1;
		wait(&l);
		childPID = -1;
		mvwprintw(winstatus, 4, 2, "Server Online: false");
		wrefresh(winstatus);
	}
}

void webserverMenu::goHomeYourDrunk() {
	int i;
	shutDownWebServer();
	close(socket_desc);
	unpost_menu(menu);
	free_menu(menu);
	for (i = 0; i <= 3; i++) {
		free_item(item[i]);
	}
	free(item);
	delwin(pad);
	endwin();
}


void webserverMenu::addLogMsg(const string &msg) {
	static int counter = 5;
	static int currRow = 0;
	waddstr(pad, (msg + string("\n")).c_str());
	if (counter > 0) {
		prefresh(pad, 0, 0, 16, 2, 22, COLS - 2);
		counter--;
	} else {
		prefresh(pad, currRow++, 0, 16, 2, 22, COLS - 2);
	}
}

void webserverMenu::setNewClient(const string &client) {
    mvwprintw(winstatus, 5, 2, ("Client:                "));
    mvwprintw(winstatus, 5, 2, ("Client: " + client).c_str());
	wrefresh(winstatus);
}

void webserverMenu::incrementClientCounter() {
    mvwprintw(winstatus, 6, 2, ("Connection No.: " + to_string(++clientCounter)).c_str());
	wrefresh(winstatus);
}

int webserverMenu::getSocket_desc() {
	return socket_desc;
}
