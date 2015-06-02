/*
 ============================================================================
 Name        : socketsCliente.c
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

int main(int argc,char* argv[]) {
	struct addrinfo hints, *res;
	int sockfd,err;
	char msg[BUFFER_SIZE];


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((err=getaddrinfo(argv[1], argv[2], &hints, &res)) != 0){
		gai_strerror(err);
		exit(1);
	}

	if((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) ==-1){
		perror("socket");
		exit(1);
	}

	if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1){
		perror("connect");
		exit(1);
	}

	printf("conexion establecida");
	close(sockfd);
	return 0;
}
