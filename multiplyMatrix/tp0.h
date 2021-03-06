	#ifndef TP0_H_
	#define TP0_H_
	#define _GNU_SOURCE
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <stdbool.h>


	#define SIZE_MAT 50

	void printHelp();
	void printLinea(int fil, int col, double* matrix);
	void finally(double* m1,double* m2,double* out);

	double* leerMatriz(int* fil, int* col);

	int  checkArguments(int,char*[]);

	extern void multiplicarMatrices(int f1, int c1, int f2, int c2, double* m1, double* m2, double* out);

	//void multiplicarMatrices(int f1, int c1, int f2, int c2, double* m1, double* m2, double* out);


	#endif /* TP0_H_ */
