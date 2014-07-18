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
    //parse cmd args
    if ( argc < 3 )
    {
	cout << "Needs directories to send to server" << endl;
	return 1;
    }
    //first arg should be the hostname

    char **args = new char *[argc];
    for(int i = 2 ; i < argc; i++)
    {
	args[i-2] = new char;
	strcpy(args[i-2], argv[i]);
    }
    
    initConnection(argv[1]);
    
    
    //send server the list of directories
    char *msg[] = { "/bin",
		    "/etc" };
    //send number of args first
    int numArgs = argc-2;
    write(sockfd, &numArgs, sizeof(int));
    sleep(1);
    for(int i = 0; i < argc-2; i++)
    {
	write(sockfd, args[i], strlen(args[i]));
	sleep(1);
    }
    cout << "Client getting output... " << endl;
    string out;
    dup2(sockfd, STDIN_FILENO);
    while(getline(cin, out))
    {
	cout << out << endl;
    }
    cout << "Client closing" << endl;
    close(sockfd);

    //clear memory
    for(int i = 0 ; i < numArgs; i++)
    {
	delete args[i];
    }
    delete [] args;
    return 0;
}
