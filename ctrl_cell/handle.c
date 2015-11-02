/*
 * handle.c
 *
 *  Created on: Nov 2, 2015
 *      Author: wing
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"handle.h"
char * rtrim(char * str);

void handle(char * buf, int n) {
	char flag[3];
	char * delim = " ";
	strncpy(flag, strtok(buf, delim), 3);
	printf("flag='%s'\n",flag);
	if (!strcmp(flag, "MAK")) {
		char *cell_name = strtok(NULL, delim);
		char shell[100] = "make -C../";
		strcat(shell, cell_name);
		printf("Shell ='%s'\n", shell);
		system(shell);
	}
	if (!strcmp(flag, "STA")) {
		char *cell_name = strtok(NULL, delim);
		char shell[100] = "../";
		strcat(shell, cell_name);
		printf("Shell ='%s'\n", shell);
		system(shell);
	}
	if (!strcmp(flag, "STO")) {

	}
	if (!strcmp(flag, "CPY")) {

	}
	if (!strcmp(flag, "MOV")) {

	}
	if (!strcmp(flag, "DEL")) {

	}
	if (!strcmp(flag, "PRI")) {

	}
	printf("buf = '%s'\n",buf);
}

char * rtrim(char * str) {
	int n = strlen(str) - 1;
	while (n > 0) {
		if (*(str + n) != ' ') {
			*(str + n + 1) = '\0';
			break;
		} else
			n--;
	}
	return str; /*Return a pointer to the string*/
}
