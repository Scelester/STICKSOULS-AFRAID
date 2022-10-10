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

int main(int argc, char **argv) {
//	defining file descripter
	int server_fd, client_fd;

	struct sockaddr_in server_addr, client_addr;

	socklen_t addr_size;

	char buffer[Max];

// server socket setting
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));

	listen(server_fd, 5);

	printf("[+]LISTNING ON PORT : %d\n", PORT);

	client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &addr_size);

	if (client_fd != -1) {
		printf("[+]CLIENT CONNECTED\n");
		strcpy(buffer, "This is the message");
		send(client_fd, buffer, strlen(buffer), 0);
	}

	return 0;

}
