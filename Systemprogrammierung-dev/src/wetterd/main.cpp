/*!
 * \file main.cpp
 * \brief Main Methode fuer die Aussentemperatur
 */
#include "temperatur/calcTemp.h"
#include "temperatur/tempSensor.h"
extern "C" {
	#include "ringbuffer/ringbuffer.h"
}
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include "wetterd/xmlParser.h"
#include "wetterd/weatherLoader.h"
#include "wetterd/datenbank.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/**
 * \fn void test_free(void *ptr)
 * \brief Methode zum freeeen von pointern
 */
void test_free(void *ptr) {
	free(ptr);
}
void signalBlock();
void signalUnBlock();

ring_buffer *buffer = init_buffer(10, test_free);

/**
 * \fn float calcAverage(ring_buffer *buffer)
 * \brief kalkuliert den Durchschnitt der Innentemperatur
 */

float calcAverage(ring_buffer *buffer) {
	int count = buffer->count; 
	float sum = 0;
	float *temp;
	while(buffer->count > 0) {
		temp = (float *)read_buffer(buffer);
		sum += *temp;
		free(temp);
	}
	return sum/(float)count;
}

void deleteFile() {
	if(remove("/home/pi/exists.txt") != 0) {
		syslog(LOG_INFO, "Error beim Löschen der Datei!");
	} 
}

void writeTemp() {
	TempSensor tempSensor = TempSensor(calculateTemperature);
	
			
	while(true) {
		float *temperature = (float *)malloc(sizeof(float));
		*temperature = tempSensor.getTemp();
		write_buffer(buffer, temperature);
		sleep(2);
	}
}

void sigTermHandler(int sig) {
	if(sig == SIGTERM) {
		signalBlock();
		syslog(LOG_INFO, "SIGTERM empfangen: Execution wird eingeleitet");
		deleteFile();
		free_buffer(buffer);
		closelog();
		signalUnBlock();
		exit(0);
	}	
}

void sigHupHandler(int sig) {
	if(sig == SIGHUP) {
		signalBlock();
		syslog(LOG_INFO, "SIGHUP empfangen");
		WeatherLoader *weatherLoader = new WeatherLoader();
		XmlParser xmlParser = XmlParser();
		Database database = Database();
			
		string result = weatherLoader->getWeather();
		xmlParser.parseString(result);
		string outsideTemp = xmlParser.getOutsideTemp();
		float outsideFloat = std::stof(outsideTemp, NULL);
		database.writeDatabase(outsideFloat, calcAverage(buffer));
		syslog(LOG_INFO, "Datenbank beschrieben");
		signalUnBlock();
	}
}

void sigUsr1Handler(int sig, siginfo_t *siginfo, void *ptr) {
	if(sig == SIGUSR1) {
		signalBlock();
		syslog(LOG_INFO, "SIGUSR1 empfangen");
		Database database = Database();
		string result = database.readDatabase();
		
		ofstream file("/home/pi/Systemprogrammierung/Systemprogrammierung/server/wetter/database.json");
		file << result;
		file.close();
		kill(siginfo->si_pid, SIGCONT);
		
		signalUnBlock();
		syslog(LOG_INFO, "Daten aus der Datenbank gelesen");
	}	
}

void signalBlock() {
	sigset_t mySet;
	sigemptyset(&mySet);
	sigaddset(&mySet, SIGTERM);
	sigaddset(&mySet, SIGHUP);
	sigaddset(&mySet, SIGUSR1);
	sigprocmask(SIG_SETMASK, &mySet, NULL);
}

void signalUnBlock() {
	sigset_t mySet;
	sigemptyset(&mySet);
	sigaddset(&mySet, SIGTERM);
	sigaddset(&mySet, SIGHUP);
	sigaddset(&mySet, SIGUSR1);
	sigprocmask(SIG_UNBLOCK, &mySet, NULL);
}

/**
 * Main-Methode	
 * 
 */
int main() {
	if(int f = open("/home/pi/exists.txt", O_CREAT | O_EXCL) >= 0) {
		close(f);
		pid_t p;
		switch (p = fork()) {
			case -1:
				deleteFile();
				break;
			case (pid_t)0:
				openlog("Temperatur-Daemon", LOG_PID, LOG_USER);
				setsid();
				umask(0);
				signal(SIGTERM, sigTermHandler);
				signal(SIGHUP, sigHupHandler);
				struct sigaction act;
				act.sa_sigaction = sigUsr1Handler;
				act.sa_flags = SA_SIGINFO;
				sigaction(SIGUSR1, &act, NULL);
				chdir("~");
				for (int i = 0; i < sysconf(_SC_OPEN_MAX); i++) {
					close(i);
				}
				open("/dev/null", O_RDWR);
				dup2(STDIN_FILENO, STDOUT_FILENO);
				dup2(STDIN_FILENO, STDERR_FILENO);
				
				syslog(LOG_INFO, "Temperatur-Daemon gestartet");
				writeTemp();
				break;
			default:
				exit(0);
				break;
		}
	}
	
	return 0;
}
