/*
 ============================================================================
 Name        : pruebasSockets.c
 Author      : Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#define BACKLOG 10
#define BUFFER_SIZE 128

int main(int argc, char* argv[]) {
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	struct addrinfo hints, *res;
	int sockfd, new_fd, err;
	char* buffer[BUFFER_SIZE];

	scanf("%128[^\n]s", buffer);
			getchar();
			printf("ok");

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	if ((err = getaddrinfo(NULL, argv[1], &hints, &res)) != 0) {
		gai_strerror(err);
		exit(1);
	}

	if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))
			== -1) {
		perror("socket");
		exit(1);
	}

	if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
		perror("bind");
		exit(1);
	}

	listen(sockfd, BACKLOG);
	addr_size = sizeof(struct sockaddr_in);
	while (1) {

		if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr,
				&addr_size)) == -1) {
			perror("accept");
			exit(1);
		}
		printf("conexion establecida");
	}
	close(new_fd);
	close(sockfd);
	return 0;

}
