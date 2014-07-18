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

using namespace std;

const int PORT = 51606;

int sockfd;

void initConnection(char *HOSTNAME)
{
    //connect to server
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


void getFile()
{
    //get file from the server
    //get filepath first
    char filepath[100];
    memset(filepath, 0, 100);
    read(sockfd, filepath, 99);
    cerr << "Received file " << filepath << endl;
    //take out the leading '/'
    sleep(1);
    int fd = open(filepath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
    
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
    
    initConnection(argv[1]);
    string dir(argv[2]);
    ///send directory
    string str(".");
    str+=dir;
    mkdir((char*)str.c_str(), 0777);
    write(sockfd, (char*)dir.c_str(), dir.size());
    sleep(1);
    int numFiles;
    read(sockfd, &numFiles, sizeof(int));
    cout << " got " << numFiles << " files " <<endl;
    sleep(1);
    for(int i = 0; i < numFiles; i++)
    {
	getFile();

    }
    close(sockfd);
    return 0;
}
