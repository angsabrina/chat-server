#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

struct sockaddr_in server;
int fd; 
int conn;
char message[100] = "";

int main(int argc, char *argv[]) {

	if(argc < 2) {
		fprintf(stderr, "ERROR, no address provided\n");
		exit(1);
	} else if(argc < 3) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	int portNum = atoi(argv[2]);
	// printf("server address: %s", argv[1]);
	char serverAddr[20];
	strcpy(serverAddr, argv[1]);

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		error("ERROR opening socket");
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);

	inet_pton(AF_INET, serverAddr, &server.sin_addr); //binds client to localhost
	connect(fd, (struct sockaddr *)&server, sizeof(server)); //connects client to server

	while(1) {
		printf("Enter a message: ");
		fgets(message, 100, stdin);
		send(fd, message, strlen(message), 0);
	}

	return 0;
}