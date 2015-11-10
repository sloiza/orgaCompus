
#include "tp0.h"

void printHelp() {
	char *help = "Usage:"
			"\t ./tp0 -h \n"
			"\t ./tp0 -V \n"
			"\t ./tp0 < in_file > out_file \n"
			"Options: \n"
			" -V, --version \n\t Print version and quit. \n"
			" -h, --help \n\t Print this information and quit.\n"
			" Examples: \n"
			"  ./tp0 < in.txt > out.txt \n"
			"  cat in.txt | ./tp0 > out.txt \n";

	printf("%s", help);
}

void printLinea(int fil, int col, double* matrix){
	printf("%dx%d ", fil, col);
	if (ferror(stdout)){
		fprintf(stderr, "Error printing stdout\n");
		free(matrix);
		matrix = NULL;
		exit(EXIT_FAILURE);
	}
	for(int i=0;i<fil*col;i++){
		printf(" %lf",matrix[i]);
		if (ferror(stdout)){
			fprintf(stderr, "Error printing stdout\n");
			free(matrix);
			matrix = NULL;
			exit(EXIT_FAILURE);
		}
	}
	printf("\n");
	if (ferror(stdout)){
		fprintf(stderr, "Error printing stdout\n");
		free(matrix);
		matrix = NULL;
		exit(EXIT_FAILURE);
	}
}
int checkArguments(int cantidadArgumentos, char* argumentos[]) {
	int retorno = 1;
	if ((cantidadArgumentos == 2)
			&& ((strcmp(argumentos[1], "-h") == 0)
					|| (strcmp(argumentos[1], "--help") == 0))) {
		printHelp();
		retorno = 0;
	} else if ((cantidadArgumentos == 2)
			&& (((strcmp(argumentos[1], "-V") == 0))
					|| (strcmp(argumentos[1], "--version") == 0) || (strcmp(argumentos[1], "-v") == 0))) {
		printf("Version 1.0\n");
		retorno = 0;
	}

	return retorno;
}

// void multiplicarMatrices(int f1, int c1, int f2, int c2, double* m1, double* m2, double* out) {
//
//  int pos = 0;
// 	int i,j,k, m;
// 	for( i =0 ; i < f1*c1; i=i+c1){
// 		for(k=0; k < c2 ; k++){
// 			double sum = 0.0;
// 			m = i;
// 			// printf("Entro for de K con k = %d\n",k );
// 			for(j=k; j < f2*c2; j=j+c2){
// 				sum+= m1[m]*m2[j];
// 				m++;
// 			}
// 			out[pos] = sum;
// 			pos++;
// 		}
// 	}
// }
//

double* leerMatriz(int* fil, int* col ){
	char x;
	double* m = NULL;
	double value = 0.0;
	int cantNums;
	if(( fscanf(stdin, "%d %c %d", fil, &x, col )==3) && !feof(stdin)){
		if (ferror (stdin)){
			printf ("Error reading stdin\n");
			if(m!=NULL){
				free(m);
				m = NULL;
			}
			exit(EXIT_FAILURE);
		}
		cantNums = (*fil) * (*col);
		m = (double*) malloc(sizeof(double)*cantNums);
		if(m == NULL){
			fprintf(stderr, "Error malloc \n");
		}

		for(int j =0;j<cantNums; j++){
			if(fscanf(stdin, "%lf", &value) ==1){
				if (ferror (stdin)){
					printf ("Error reading stdin\n");
					if(m!=NULL){
						free(m);
						m = NULL;
					}
					exit(EXIT_FAILURE);
				}
				m[j] = value;
			}else{
				fprintf(stderr, "Matriz inválida \n" );
				if(m!=NULL){
					free(m);
					m = NULL;
				}
				exit(EXIT_FAILURE);
			}

		}


	}else{
		if(m!=NULL){
			free(m);
			m = NULL;
		}
		exit(EXIT_FAILURE);
	}

	return m;
}

void finally(double* m1,double* m2,double* out){
	if(m1 != NULL){
		free(m1);
		m1 = NULL;
	}
	if(m2 != NULL){
		free(m2);
		m2 = NULL;
	}
	if(out !=NULL){
		free(out);
		out = NULL;
	}
}

 int main(int argc, char *argv[])
{
	if (!checkArguments(argc,argv)){
		return 1;
	}else{
		do{
			int fil1 = 0, col1 = 0, fil2 = 0, col2 = 0;
			double* m1 = NULL;
			double* m2 = NULL;
			double* out = NULL;

			m1 = leerMatriz(&fil1, &col1 );
			m2 = leerMatriz(&fil2, &col2 );

			if (col1== fil2){
				out = (double*) malloc(sizeof(double)*fil1*col2);
				if(out == NULL){
					fprintf(stderr, "Error malloc \n");
				}
				multiplicarMatrices(fil1, col1, fil2, col2, m1, m2, out);
				printLinea(fil1, col2, out);


				finally(m1,m2,out);
			}else{
				fprintf(stderr,"Matrices incorrectas para la multiplicacion. \n");
				finally(m1,m2,out);
				exit(EXIT_FAILURE);
			}
		}while(!feof(stdin));
	}
	return 0;
}
