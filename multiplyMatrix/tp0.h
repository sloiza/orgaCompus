/*
 * tp0.h
 *
 *  Created on: 31/08/2015
 *      Author: sami
 */

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

int multiplicarMatrices(double v1[],int f1, int c1, double v2[], int f2, int c2, double m1[f1][c1], double m2[f2][c2] );


#endif /* TP1_H_ */
