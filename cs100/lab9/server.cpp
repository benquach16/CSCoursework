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
#include <pthread.h>

using namespace std;

const int PORT = 51606;
const int NUMTHREADS = 3;
int sockfd;
pthread_mutex_t print_mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;

int initServer();

void* doThread(void *threadid)
{
    long tid = (long)threadid;


    //pthread_mutex_unlock(&print_mutex);
    cout << "This is thread " << tid << endl;
    int newfd = initServer();
    vector<string> directories;
    //read list of directories from the client, ls them, and pipe the output to client

    string msg("no one loves you ");
    msg+=(char)(tid+48);

    write(newfd, (char*)msg.c_str(), msg.size());

    cerr << "PLEASE THIS IS THREAD " << tid << endl;
    sleep(1);
    //int fd = open("text.txt", O_RDWR);

    //pthread_mutex_lock(&print_mutex);
    char buffer[100];
    int size = read(newfd, buffer, 99);
    if(size==-1)
    {
	int errcode = errno;
	cerr << errcode << endl;
    }

    cerr << buffer << endl;
    string str(buffer);
    str +=(char)(tid+48);
    pthread_mutex_lock(&print_mutex);
    int fd = open("text.txt", O_RDWR | O_APPEND);
    write(fd, (char*)str.c_str(), str.size());

    pthread_mutex_unlock(&print_mutex);
    sleep(1);
    char buf[100];
    read(fd, buf, 99);
    write(newfd, buf, 99);
    //write(fd, buffer, size);
    close(sockfd);
    close(newfd);    
    close(fd);

    //pthread_mutex_unlock(&print_mutex);
    pthread_exit(0);
    return 0;
}

int initServer()
{
    struct sockaddr_in client_addr;
    int sin_size = sizeof(struct sockaddr_in);
    int newfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&sin_size);
    if(newfd == -1)
	cerr << "accept has failed()" << endl;
    else
	cerr << "accept is OK" << endl;
    return newfd;
}

int main()
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
    //initServer();
    pthread_t threads[3];
    pthread_mutex_init(&print_mutex, 0);
    pthread_mutex_lock(&print_mutex);
    for (long i = 0; i < 3; i++)
    {
	
	pthread_create(&threads[i], 0, doThread,(void*)i);
    }
    pthread_mutex_unlock(&print_mutex);
    for(int i = 0; i < 3; i++)
	pthread_join(threads[i], 0);
    pthread_mutex_destroy(&print_mutex);
    pthread_exit(0);
    return 0;
}
