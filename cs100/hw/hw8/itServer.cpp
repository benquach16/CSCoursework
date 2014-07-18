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
#include <vector>
#include <fcntl.h>
#include <dirent.h>

using namespace std;

const int PORT = 51606;
int sockfd, newfd;

void execute(char *filepath)
{
    //FORK AND DUP2
    int pid = fork();
    switch(pid)
    {
    case -1:
    {
	//HANDLE ERRO
	int errcode = errno;
	cerr << "forke() failed with code : " << errcode << endl;
	exit(1);
	break;
    }
    case 0:
    {
	//DO CHILD STUFF    
	
	cout << "ls " << filepath << endl;
	if(execlp("ls", "ls", "-l", filepath, 0)==-1)
	{
	    int errcode = errno;
	    cerr << "execlp() failed with code : " << errcode << endl;
	}
	exit(1);
	break;
    }
    default:
    {
	//WAIT
	int status;
	waitpid(-1, &status, 0);
	close(sockfd);
	close(newfd);
	break;
    }
    }
}

void runLs(char *filepath)
{
    //HERES WHAT WE DO TEAM
    //FIRST WE SCAN THROUGH THE DIRECTORY AND GET A FILEPATH OF ALLL THE FILES
    //THEN WE FORK AND LS A TON OF TIMES
    DIR *dirp = 0;
    dirp = opendir(filepath);
    int numFiles = 0;
    if(!dirp)
    {
	cerr << filepath << " directory could not be opened" << endl;
	exit(1);
    }
    dirent *direntp;
    vector<string> filePaths;
    while (direntp = readdir (dirp ))
    {
	struct stat st;
	string str(filepath);
	str+='/';
	str+=direntp->d_name;
	char *arg = (char*)str.c_str();
	if(stat(arg, &st)==-1)
	{
	    int errcode = errno;
	    cerr << "stat() failed with code " << errcode << endl;
	    exit(1);
	}

	if(S_ISREG(st.st_mode))
	{
	    //filePaths.push_back(arg);
	    execute(arg);
	}
	
    }

    for(int i = 0; i < filePaths.size(); i++)
    {
	//execute((char*)filePaths[i].c_str());
    }
}

void initServer()
{
    //important to read errno of socket calls because they are more errror prone
    //initialize server
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    //lots of code block
    memset(&(server_addr.sin_zero), 0, 8);
    //bind here
    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(sockaddr))==-1)
    {
	//make sure we know if bind failed because that means
	//socket has not been cleared
	int errcode = errno;
	cerr << "Bind() failed with code " << errcode << endl;
	exit(1);
    }
    else
    {
	cerr << "Bind() successful" <<endl;
    }
    
    if(listen(sockfd, 10)==-1)
    {
	//usually doesnt occur
	int errcode = errno;
	cerr << "Listen() failed with code " << errcode << endl;
	exit(1);
    }
    else
    {
	cerr << "Listen() successful" << endl;
    }

    int sin_size = sizeof(struct sockaddr_in);
    cerr << "going to accept" << endl;
    
    newfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&sin_size);
    if(newfd == -1)
	cerr << "accept has failed()" << endl;
    else
	cerr << "accept is OK" << endl;
}

int main()
{

    initServer();
    vector<string> directories;
    //read list of directories from the client, ls them, and pipe the output to client
    int numArgs;
    read(newfd, &numArgs, sizeof(int));
    cerr << "got " << numArgs << " directories" << endl;
    sleep(1);
    for(int i = 0; i < numArgs; i++)
    {
	char buffer[300];
	read(newfd, buffer, 299);
	cerr << "reading...." << endl;
	cerr << buffer << endl;
	directories.push_back(buffer);
	sleep(1);
    }

    if(dup2(newfd, STDOUT_FILENO)==-1)
    {
	int errcode = errno;
	cerr << "dup2() failed with code " << errcode << endl;
    }
    for(unsigned i = 0; i < directories.size(); i++)
    {
	runLs((char*)directories[i].c_str());
    }
    close(sockfd);
    close(newfd);
    
    return 0;
}
