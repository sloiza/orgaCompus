/*
 * tp0.h
 *
 *  Created on: 31/08/2015
 *      Author: sami
 */

#ifndef TP0_H_
#define TP0_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE_MAT 100


void printHelp();

int  checkArguments(int,char*[]);

/* Read a file and return a matrix */
float* processFile(FILE* file);

#endif /* TP1_H_ */


#endif /* TP0_H_ */
