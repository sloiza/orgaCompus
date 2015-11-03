
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



 int main(int argc, char *argv[])
{
	if (!checkArguments(argc,argv)){
		return 1;
	}else{
		int i = 1;
		do{
			int bytes_now=0, bytes_consumed = 0;
			char buffer[SIZE_MAT];

			int fil1 = 0, col1 = 0, fil2 = 0, col2 = 0;
			int cantNums1 = 0, cantNums2 = 0;
			double* m1 = NULL;
			double* m2 = NULL;
			char x;
			double v1 = 0.0,v2 = 0.0;
			//leo matriz 1
			if(( fscanf(stdin, "%d %c %d", &fil1, &x, &col1 )==3) && !feof(stdin)){
				cantNums1 = fil1 * col1;
				m1 = (double*) malloc(sizeof(double)*cantNums1);
				if (ferror (stdin)) printf ("Error reading stdin\n");
				for(int j =0;j<cantNums1; j++){
					if(fscanf(stdin, "%lf", &v1) ==1){
						m1[j] = v1;
					}else if (ferror (stdin)){
						fprintf(stderr, "Error reading stdin\n");
						if(m1!=NULL){
							free(m1);
							m1 = NULL;
						}
						exit(EXIT_FAILURE);
					}else{
						fprintf(stderr, "Matriz %d inválida \n", i);
						if(m1!=NULL){
							free(m1);
							m1 = NULL;
						}
						exit(EXIT_FAILURE);
					}

				}
				i++;


			}else if (ferror (stdin)){
				fprintf(stderr, "Error reading stdin\n");
				if(m1!=NULL){
					free(m1);
					m1 = NULL;
				}
				exit(EXIT_FAILURE);
			}else{
				if(m1!=NULL){
					free(m1);
					m1 = NULL;
				}
				exit(EXIT_FAILURE);
			}
			if((fscanf(stdin, "%d %c %d", &fil2, &x, &col2 ) == 3) && !feof(stdin)){
				cantNums2 = fil2 * col2;
				m2 = (double*) malloc(sizeof(double)*cantNums2);
				if (ferror (stdin)) printf ("Error reading stdin\n");

				for(int j =0;j<cantNums2; j++){
					if(fscanf(stdin, "%lf", &v2) ==1){
						m2[j] = v2;
					}else if (ferror (stdin)){
						fprintf(stderr, "Error reading stdin\n");
						if(m2!=NULL){
							free(m2);
							m2 = NULL;
						}
						exit(EXIT_FAILURE);
					}else{
						fprintf(stderr, " Matriz %d incorrecta \n", i);
						if(m2!=NULL){
							free(m2);
							m2 = NULL;
						}
						exit(EXIT_FAILURE);
					}
				}
				i++;
			}else if (ferror (stdin)){
				fprintf(stderr, "Error reading stdin\n");
				if(m2!=NULL){
					free(m2);
					m2 = NULL;
				}
				exit(EXIT_FAILURE);
			}else{
				fprintf(stderr, " Matriz %d incorrecta \n", i);
				if(m2!=NULL){
					free(m2);
					m2 = NULL;
				}
				exit(EXIT_FAILURE);
			}

			if (col1== fil2){
				double* out = (double*) malloc(sizeof(double)*fil1*col2);
				multiplicarMatrices(fil1, col1, fil2, col2, m1, m2, out);
				bytes_consumed = 0;
				memset (buffer,0,SIZE_MAT);
				sprintf(buffer+ bytes_consumed,"%dx%d%n\n", fil1,col2, & bytes_now);
				bytes_consumed += bytes_now;
				for(int i=0;i<fil1*col2;i++){
					sprintf(buffer+ bytes_consumed," %lf%n",out[i], & bytes_now);
					bytes_consumed += bytes_now;
				}
				puts(buffer);
				if (ferror(stdout)){
					fprintf(stderr, "Error printing stdin\n");
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
					exit(EXIT_FAILURE);
				}



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
			}else{
				fprintf(stderr,"Matrices incorrectas para la multiplicacion. \n");
				if(m1 != NULL){
					free(m1);
					m1 = NULL;
				}
				if(m2 != NULL){
					free(m2);
					m2 = NULL;
				}
				exit(EXIT_FAILURE);
			}
		}while(!feof(stdin));
	}
	return 0;
}
