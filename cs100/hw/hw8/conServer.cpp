#include <iostream>
#include <dirent.h>
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
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>


using namespace std;

const int PORT = 51606;

int sockfd, newfd;

void writeFile(char*);

void initServer()
{

    //initialize server
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    memset(&(server_addr.sin_zero), 0, 8);
    //make sure to bind
    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(sockaddr))==-1)
    {
	//if bind failes its because of socket error
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
    
}

void openDir(char *pathname)
{
    DIR *dirp = 0;
    dirp = opendir(pathname);
    int numFiles = 0;
    if(!dirp)
    {
	cerr << pathname << " directory could not be opened" << endl;
	
    }
    dirent *direntp;
    vector<string> filePaths;
    while (direntp = readdir (dirp ))
    {
	struct stat st;
	string str(pathname);
	str+='/';
	str+=direntp->d_name;
	char *arg = (char*)str.c_str();
	stat(arg, &st);
	if(direntp->d_name[0] != '.' && direntp->d_name[1] != '.')
	{
	    if(S_ISREG(st.st_mode))
	    {
		//cerr << "file " << arg << endl;
		filePaths.push_back(arg);
		cerr << direntp->d_type << endl;
		//send file to client
		numFiles++;
		
	    }
	    else if(S_ISDIR(st.st_mode))
	    {
		//cerr << "dir " << arg << endl;
		//openDir(arg);
	    }
	}
    }
    //send the numfiles as an int
    write(newfd, &numFiles, sizeof(numFiles));
    sleep(1);
    for(int i = 0; i < filePaths.size(); i++)
    {
	//cout << filePaths[i] << endl;
	writeFile((char*)filePaths[i].c_str());
	sleep(1);
    }
    closedir(dirp);
}

void writeFile(char *filepath)
{
    
    //send two parts
    //the filepath and then the content!!!!
    //make sure we take out the leading '/'
    string str(filepath);
    str.erase(0, 1);
    write(newfd, (char*)str.c_str(), str.size());
    int fd = open(filepath, O_RDONLY);
    sleep(1);
    while(1)
    {
	char buf[200000];
	memset(buf, 0, 200000);
	int size=read(fd, buf, 199999);
	sleep(1);
	if(!size)
	{
	    char i[] = "STOPFILEREAD";
	    write(newfd, i, 12);
	    //cerr << "Server reached EOF" << endl;
	    break;
	}
	write(newfd, buf, size);
	usleep(500);
    }    
}

int main()
{
    initServer();
    while(1)
    {
	struct sockaddr_in client_addr;
	int sin_size = sizeof(sockaddr_in);
	newfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&sin_size);
	if(newfd == -1)
	    cerr << "accept has failed()" << endl;
	else
	    cerr << "accept is OK" << endl;
	//fork so we handle unlimited clients
	int pid = fork();
	
	if(!pid)
	{
	    //get directory from client
	    char buffer[300];
	    read(newfd, buffer, 299);
	    cout << buffer << endl;
	    sleep(1);
	    cout << "reading directory... " << endl;
	    string str(buffer);
	    //open the directory in c and copy the files over
	    openDir(buffer);
	}
	else if(pid > 0)
	{
	    close(newfd);
	}
	else
	{
	    int errcode = errno;
	    cerr << "Fork failed " << errcode << endl;
	}
    }
    close(sockfd);
    close(newfd);
    return 0;
}
