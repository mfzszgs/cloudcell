/*
 * ctrl_cell.c
 *
 *  Created on: Oct 31, 2015
 *      Author: wing
 */

#include "contiki.h"

#include <stdio.h> /* For printf() */
#include <unistd.h>
#include "mysock.h"
#include "handle.h"
/*---------------------------------------------------------------------------*/
PROCESS(ctrl_cell, "ctrl_cell");
AUTOSTART_PROCESSES(&ctrl_cell);
/*---------------------------------------------------------------------------*/

void str_echo(int connfd);

PROCESS_THREAD( ctrl_cell, ev, data) {
	PROCESS_BEGIN();

	serv_sock(8080, str_echo);

	PROCESS_END();
}

void str_echo(int connfd) {
	ssize_t n;
	char buf[100];
	while ((n = read(connfd, buf, 100)) > 0) {
		printf("GET buf='%s'\n", buf);
		handle(buf, n);
		writen(connfd, buf, n);
	}
	while (n < 0 && errno == EINTR) {
		while ((n = read(connfd, buf, 100)) > 0) {
			printf("GET buf='%s'\n", buf);
			handle(buf, n);
			writen(connfd, buf, n);
		}
	}
	if (n < 0)
		printf("str_echo:read error");
}
