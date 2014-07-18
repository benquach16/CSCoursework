/*
 * Course: CS 100 Fall 2013
 *
 * First Name: Benjamin
 * Last Name: Quach
 * Username: bquac002
 * email address: bquac002@ucr.edu
 *
 *
 * Assignment: hw9
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA. */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <vector>
#include <pthread.h>

using namespace std;

const int PORT = 51606;


pthread_mutex_t print_mutex;

int initConnection(char*);

void getFile(int, int);

char *host;
char *directory;

void* doThread(void *threadid)
{
    long tid = (long)threadid;
    cerr << "Client thread: " << tid << endl;
    int sockfd = initConnection(host);
    string dir(directory);
    ///send directory

    string str("thread");
    str+=(char)(tid+48);
    
    //str+=dir;
    cerr << "creading folder " << str << endl;
    mkdir((char*)str.c_str(), 0777);
    str +=dir;
    mkdir((char*)str.c_str(), 0777);
    write(sockfd, (char*)dir.c_str(), dir.size());
    sleep(1);
    int numFiles;
    read(sockfd, &numFiles, sizeof(int));
    cout << " got " << numFiles << " files " <<endl;
    sleep(1);
    for(int i = 0; i < numFiles; i++)
    {
	getFile(sockfd, tid);

    }
    close(sockfd);  
    pthread_exit(0);
  
}

int initConnection(char *HOSTNAME)
{
    //connect to server
    struct sockaddr_in server_addr;

    struct hostent *he;
    he = gethostbyname(HOSTNAME);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(server_addr.sin_zero), 0, 8);

    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))==-1)
    {
	cerr << "Connect() failed" << endl;
    }
    else
    {
	cerr << "Connect() successful" << endl;
    }
    return sockfd;
}


void getFile(int sockfd, int tid)
{
    //get file from the server
    //get filepath first
    //mutex lockin dont work non
    //pthread_mutex_lock(&print_mutex);    
    char filepath[100];
    memset(filepath, 0, 100);
    read(sockfd, filepath, 99);
    //take out the leading '/'
    string dir(directory);
    ///send directory

    string str("thread");
    str+=(char)(tid+48);
    str+="/";
    str+=filepath;

    cerr << "Received file " << str << endl;
    sleep(1);
    int fd = open((char*)str.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
    
    while(1)
    {
	char buffer[200000];
	memset(buffer, 0, 200000);
	int size = read(sockfd, buffer, 199999);
	//sleep(1);
	//we have a really getto way of getting EOF
	if(buffer[0] == 'S' && buffer[1] == 'T' && buffer[2] == 'O'
	    && buffer[3] == 'P' && buffer[4] == 'F' && buffer[5] == 'I')
	{
	    break;
	}
	//cerr << buffer << endl;
	write(fd, buffer, size);
	usleep(500);
    }
}

int main(int argc, char *argv[])
{
    //connect to server
    if(argc < 3)
    {
	//not enough args
	cerr << "Did not supply hostname and directory to copy" << endl;
	exit(1);
    }
    host = argv[1];
    directory = argv[2];
    //before we init connection, pthread it
    pthread_t threads[10];
    pthread_mutex_init(&print_mutex,0);
    pthread_mutex_lock(&print_mutex);
    for(long i = 0; i < 10; i++)
    {
	pthread_create(&threads[i], 0, doThread, (void*)i);
    }
    pthread_mutex_unlock(&print_mutex);
    for(int i = 0; i < 10; i++)
    {
	pthread_join(threads[i], 0);
    }
    pthread_mutex_destroy(&print_mutex);
    pthread_exit(0);
    return 0;
}
