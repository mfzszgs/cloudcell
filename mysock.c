/*
 * mysock.c
 *
 *  Created on: Oct 31, 2015
 *      Author: wing
 */
#include "mysock.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

size_t /* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n) {
	size_t nleft;
	size_t nwritten;
	const char *ptr;

	ptr = (char*) vptr;
	nleft = n;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return (-1); /* error */
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return (n);
}

void serv_sock(unsigned short int port, void (*handle)(char* string, int size)) {

	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 10);

	for (;;) {
		clilen = sizeof(cliaddr);
		if ((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen))
				< 0) {
			if (errno == EINTR)
				continue; /* back to for() */
			else
				printf("accept error");
		}

		if ((childpid = fork()) == 0) { /* child process */
			close(listenfd); /* close listening socket */
			/* process the request */
//			ssize_t n;
//			char buf[100];
//			while ((n = read(connfd, buf, 100)) > 0)
//				handle(buf, n);
//
//			while (n < 0 && errno == EINTR) {
//				while ((n = read(connfd, buf, 100)) > 0)
//					handle(buf, n);
//			}
//			if (n < 0)
//				printf("str_echo:read error");

			ssize_t n;
			char buf[100];
			while ((n = read(connfd, buf, 100)) > 0)
				writen(connfd, buf, n);
			while (n < 0 && errno == EINTR) {
				while ((n = read(connfd, buf, 100)) > 0)
					writen(connfd, buf, n);
			}
			if (n < 0)
				printf("str_echo:read error");

			exit(0);
		}
		close(connfd); /* parent closes connected socket */

	}

}

int cli_sock(char * ip, unsigned short int port) {
	int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &servaddr.sin_addr);
	connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	return sockfd;
}

void cli_close(int sockfd) {
	close(sockfd);
}
