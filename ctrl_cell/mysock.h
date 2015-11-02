/*
 * mysock.h
 *
 *  Created on: Oct 31, 2015
 *      Author: wing
 */

#ifndef MYSOCK_H_
#define MYSOCK_H_

#define MAXLINE 100

/**
 * Create a server socket.
 *
 * \param port.
 *
 * \param handle.
 */
void serv_sock(unsigned short int port, void (*handle)(int sockfd));

/**
 * Create a server socket.
 *
 * \param ip.
 *
 * \param port.
 *
 * \return The sockfd of the client;
 */
int cli_sock(char * ip, unsigned short int port);

/**
 * Close the sockfd.
 */
void cli_close(int sockfd);

#include<stddef.h>
#include <errno.h>

size_t /* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n);

size_t /* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n);

size_t readline(int fd, void *vptr, size_t maxlen);

#endif /* MYSOCK_H_ */
