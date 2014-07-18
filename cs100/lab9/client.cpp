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
#include <dirent.h>
#include <sys/stat.h>
#include <vector>

using namespace std;

const int PORT = 51606;


int sockfd;

void initConnection(char *HOSTNAME)
{

    struct sockaddr_in server_addr;

    struct hostent *he;
    he = gethostbyname(HOSTNAME);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
}


//Client needs to connect to the server and get list of directories
int main(int argc, char *argv[])
{
    
    initConnection(argv[1]);
    
    
    //send number of args first
    int numArgs = argc-2;
    char buffer[100];
    read(sockfd, buffer, 99);
    sleep(1);
    cout << buffer << endl;

    cerr<<"client writing crap" << endl;
    sleep(1);
    char msg[] = "client adding some crap ";
    if(write(sockfd, msg, strlen(msg))==-1)
    {
	int errcode = errno;
	cerr << errcode << endl;
    }
    char buf[100];
    sleep(1);
    read(sockfd, buf, 99);
    cerr << buf << endl;
    cout << "Client is exiting" << endl;
    
    return 0;
}
