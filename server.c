#include <stdio.h>
#include <sys/socket.h> //For Sockets
#include <stdlib.h>
#include <netinet/in.h> //For the AF_INET (Address Family)

/*
I am going to establish a connection for client and server through a socket
Socket is one end of an interprocess communication channel

Server's job: 
	- Create socket with socket() sys call
	- bind socket to address (port num on host machine) using bind. 
	- listen for connections with listen() 
	- accept connection with accept() (blocks until client connects with server)
	- send and receive data
*/

struct sockaddr_in serv; //main socket variable
int fd; //socket file descriptor, used to identify socket
int conn; //connection file descriptor, used to identify client connections
char message[100] = ""; //array store msgs sent by server

//
int main(int argc, char *argv[]) {
	serv.sin_family = AF_INET;
