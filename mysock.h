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
void serv_sock(unsigned short int port, void (*handle)(char* string, int size));

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

#endif /* MYSOCK_H_ */
