#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

struct sockaddr_in server;
int fd; 
int conn;
char message[100] = "";

int main() {

	fd = socket(AF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(8096);

	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); //binds client to localhost
	connect(fd, (struct sockaddr *)&server, sizeof(server)); //connects client to server

	while(1) {
		printf("Enter a message: ");
		fgets(message, 100, stdin);
		send(fd, message, strlen(message), 0);
	}

	return 0;
}