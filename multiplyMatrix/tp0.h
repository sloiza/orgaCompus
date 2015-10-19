	#ifndef TP0_H_
	#define TP0_H_
	#define _GNU_SOURCE
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	// #include <error.h>
	// #include <errno.h>
	#include <stdbool.h>


	#define SIZE_MAT 100


	void printHelp();

	int  checkArguments(int,char*[]);

	int validoLinea(char *linea);
	extern int multiplicarMatrices(int f1, int c1, int f2, int c2, double* m1, double* m2, double* out);


//	int multiplicarMatrices(int f1, int c1, int f2, int c2, double* m1, double* m2, double* out);


	#endif /* TP0_H_ */
