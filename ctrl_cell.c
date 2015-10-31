/*
 * ctrl_cell.c
 *
 *  Created on: Oct 31, 2015
 *      Author: wing
 */

#include "contiki.h"
#include "mysock.h"

#include <stdio.h> /* For printf() */
#include "mysock.h"
/*---------------------------------------------------------------------------*/
PROCESS(ctrl_cell, "ctrl_cell");
AUTOSTART_PROCESSES(&ctrl_cell);
/*---------------------------------------------------------------------------*/
void handle(char* string, int size) {
	printf("GET");
}
PROCESS_THREAD( ctrl_cell, ev, data) {
	PROCESS_BEGIN();

	serv_sock(8081, handle );

	PROCESS_END();
}
