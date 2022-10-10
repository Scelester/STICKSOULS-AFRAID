#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5555
#define Max 1024

void main() {

	int client_fd, server_fd;

	struct sockaddr_in serverAddr;
	char buf[Max];

	client_fd = socket(PF_INET, SOCK_STREAM, 0);
	printf("Client socket Created Successfully...\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	server_fd = connect(client_fd, (struct sockaddr*) &serverAddr,
			sizeof(serverAddr));

	printf("Connected to Server Successfully...\n");

	recv(client_fd, buf, Max, 0);

	printf("recieved = %s\n",buf);

	printf("Closing Connection...\n");

}
