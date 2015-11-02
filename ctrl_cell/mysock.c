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
#include<arpa/inet.h>

void serv_sock(unsigned short int port, void (*handle)(int sockfd)) {

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
//			while ((n = read(connfd, buf, 100)) > 0){
//				printf("GET\n");
//				writen(connfd, buf, n);
//			}
//			while (n < 0 && errno == EINTR) {
//				while ((n = read(connfd, buf, 100)) > 0)
//					writen(connfd, buf, n);
//			}
//			if (n < 0)
//				printf("str_echo:read error");
			handle(connfd);
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
/* end writen */
size_t /* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n) {
	size_t nleft;
	size_t nread;
	char *ptr;

	ptr = (char*) vptr;
	nleft = n;
	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return (-1);
		} else if (nread == 0)
			break; /* EOF */

		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft); /* return >= 0 */
}

/* end readn */

static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static size_t my_read(int fd, char *ptr) {

	if (read_cnt <= 0) {
		again: if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return (-1);
		} else if (read_cnt == 0)
			return (0);
		read_ptr = read_buf;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return (1);
}

size_t readline(int fd, void *vptr, size_t maxlen) {
	size_t n, rc;
	char c, *ptr;

	ptr = (char*) vptr;
	for (n = 1; n < maxlen; n++) {
		if ((rc = my_read(fd, &c)) == 1) {
			*ptr++ = c;
			if (c == '\n')
				break; /* newline is stored, like fgets() */
		} else if (rc == 0) {
			*ptr = 0;
			return (n - 1); /* EOF, n - 1 bytes were read */
		} else
			return (-1); /* error, errno set by read() */
	}

	*ptr = 0; /* null terminate like fgets() */
	return (n);
}

size_t readlinebuf(void **vptrptr) {
	if (read_cnt)
		*vptrptr = read_ptr;
	return (read_cnt);
}
/* end readline */
