#include <stdio.h>
#include <sys/socket.h> //For Sockets
#include <stdlib.h>
#include <netinet/in.h> //For the AF_INET (Address Family)
#include <errno.h>
#include <string.h>

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

//hardcoded port
// int main() {
// 	serv.sin_family = AF_INET;
// 	serv.sin_port = htons(8096); //converts unsign short to network byte order, literally "host to network short"
// 	serv.sin_addr.s_addr = INADDR_ANY; //binds the socket to all available interfaces
// 	//server.sin_addr.s_addr = inet_addr("127.0.0.1") binds to localhost only

// 	fd = socket(AF_INET, SOCK_STREAM, 0); //creates new socket and returns identifier of socket into fd
// 	if(fd < 0) {
// 		error("ERROR opening socket");
// 	}

// 	bind(fd, (struct sockaddr *)&serv, sizeof(serv)); //assigns addr specified by serv to socket
// 	listen(fd, 5); //listen for client connections, max 5 allow

// 	while(conn = accept(fd, (struct sockaddr *)NULL, NULL)) {
// 		int pid;
// 		if((pid = fork()) == 0) {
// 			while(recv(conn, message, 100, 0) > 0) {
// 				printf("Message received: %s\n", message);
// 				//extra breaking condition to terminate child process
// 				memset(message, 0, sizeof(message));
// 			}
// 			exit(0);
// 		}
// 	}
// 	return 0;
// }


//choose your own address and port
int main(int argc, char *argv[]) {
	// printf("arg nums: %i", argc);

	if(argc < 2) {
		fprintf(stderr, "ERROR, no address provided\n");
		exit(1);
	} else if(argc < 3) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	int portNum = atoi(argv[2]);
	//printf("port num: %i", portNum);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		error("ERROR opening socket");
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(portNum);
	serv.sin_addr.s_addr = inet_addr(argv[1]);

	bind(fd, (struct sockaddr *)&serv, sizeof(serv));
	listen(fd, 5);

	while(conn = accept(fd, (struct sockaddr *)NULL, NULL)) {
		int pid;
		if((pid = fork()) == 0) {
			while(recv(conn, message, 100, 0) > 0) {
				printf("Message received: %s\n", message);
				memset(message, 0, sizeof(message));
			}
			exit(0);
		}
	}
	return 0;
}


