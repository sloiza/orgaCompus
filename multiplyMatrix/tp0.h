#ifndef TP0_H_
#define TP0_H_
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdbool.h>


#define SIZE_MAT 100


void printHelp();

int  checkArguments(int,char*[]);

int validoLinea(char *linea);


#endif /* TP0_H_ */
