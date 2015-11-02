/*
 * mr_cell.c
 *
 *  Created on: Oct 31, 2015
 *      Author: wing
 */

#include "contiki.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(mr_cell, "mr_cell");
AUTOSTART_PROCESSES(&mr_cell);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD( mr_cell, ev, data) {
	PROCESS_BEGIN();

	printf("Hello, world\n");
    exit(0);

	PROCESS_END();
}
