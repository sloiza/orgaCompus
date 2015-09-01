/*
 * tp0.c
 *
 *  Created on: 31/08/2015
 *      Author: sami
 */

#include "tp0.h"

void printHelp() {
	char *help = "Usage:"
			"\t tp0 -h \n"
			"\t tp0 -V \n"
			"\t tp0 < in_file > out_file \n"
			"Options: \n"
			" -V, --version \n\t Print version and quit. \n"
			" -h, --help \n\t Print this information and quit.\n"
			" Examples: \n"
			"  tp0 < in.txt > out.txt \n"
			"  cat in.txt | tp0 > out.txt \n";

	printf("%s", help);
}
int checkArguments(int cantidadArgumentos, char* argumentos[]) {
	int retorno = 1;
	if ((cantidadArgumentos == 2)
			&& ((strcmp(argumentos[1], "-h") == 0)
					|| (strcmp(argumentos[1], "--help") == 0))) {
		printHelp();
		retorno = 0;
	} else if ((cantidadArgumentos == 2)
			&& ((strcmp(argumentos[1], "-V") == 0)
					|| (strcmp(argumentos[1], "--version") == 0))) {
		printf("Version 1.0\n");
		retorno = 0;
	}

	return retorno;
}

float* processFile(FILE* fd){


	return 0.0;
}

int main(int argc, char* argv[]){
	if (!checkArguments(argc,argv)){
		return 0;
	}else{
		// proceso
		return 1;
	}

}




