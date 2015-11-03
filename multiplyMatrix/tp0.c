
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
////	 printf("puntero a m1 3 : %p \n", m1);
////	 printf("puntero a m2 3 : %p \n", m2);
////	 for(int j =0; j< f1*c1; j++){
////		printf("CANT ELEMS 1: %d double leido del buffer %lf \n", f1*c1, m1[j]);
////	}
////	for(int j =0; j< f2 * c2; j++){
////		printf("CANT ELEMS 2: %d double leido del buffer %lf \n", f2 * c2, m2[j]);
////	}
//
//	 int pos = 0;
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

int validoLinea(double *linea){

	for(int i = 0; i < sizeof(linea);i++){

	}

	int desp =0;
	char fil = *(linea+desp);

	while( fil >='0' && fil <= '9'){
		desp++;
		fil = *(linea+desp);
	}

	if( fil != 'x'){
		fprintf (stderr,"Fila incorrecta. \n");
		return -1;
	}
	char x = *(linea+desp);

	if(!((x=='x') || (x=='X'))){
		fprintf(stderr,"Formato FxC incorrecto.  \n");
		return -1;
	}
	desp++;
	char col = *(linea+desp);
	while( col >='0' && col <= '9'){
		desp++;
		col = *(linea+desp);
	}

	int cantNums = 0;
	char car =*(linea+desp);
	if(car == ' '){
		desp++;
		car = *(linea+desp);
	}else{
		fprintf(stderr, "Bad space \n" );
	}

	while(car!= 0 && car != EOF){
		bool point = false;
		while((car != ' ' && car >= '0' && car <= '9') || (car == '.')){
			if(point && car == '.'){
				fprintf(stderr,"Valores incorrectos. \n");
				return -1;
			}else{
				if(car == '.'){
					point = true;
				}
				desp++;
				car = *(linea+desp);
			}

		}
		desp++;
		car = *(linea+desp);
		cantNums++;

	}
	return cantNums;

}


 int main(int argc, char *argv[])
{
	if (!checkArguments(argc,argv)){
		return 1;
	}else{

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
				//printf("1-  fil :%d, col: %d", fil1, col1);
				cantNums1 = fil1 * col1;
				m1 = (double*) malloc(sizeof(double)*cantNums1);
				if (ferror (stdin)) printf ("Error reading stdin\n");
				//do{
				for(int j =0;j<cantNums1; j++){
					if(fscanf(stdin, "%lf", &v1) ==1){
						//printf("value leido : %lf \n", v1 );
						m1[j] = v1;
					}else if (ferror (stdin)){
						fprintf(stderr, "Error reading stdin\n");
						if(m1!=NULL){
							free(m1);
							m1 = NULL;
						}
						exit(EXIT_FAILURE);
					}else{
						fprintf(stderr, "Reading m1. Unknown error fscanf or EOF \n");
						if(m1!=NULL){
							free(m1);
							m1 = NULL;
						}
						exit(EXIT_FAILURE);
					}

				}


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
				//printf("2 - fil :%d, col: %d", fil2, col2);
				cantNums2 = fil2 * col2;
				m2 = (double*) malloc(sizeof(double)*cantNums2);
			//	printf("puntero a m2 1 : %p \n", m2);
				if (ferror (stdin)) printf ("Error reading stdin\n");
				//do{
				for(int j =0;j<cantNums2; j++){
					if(fscanf(stdin, "%lf", &v2) ==1){
						//printf("value leido 2 : %lf \n", v2 );
						m2[j] = v2;
					}else if (ferror (stdin)){
						fprintf(stderr, "Error reading stdin\n");
						if(m2!=NULL){
							free(m2);
							m2 = NULL;
						}
						exit(EXIT_FAILURE);
					}else{
						fprintf(stderr, " Reading m2. Unknown error fscanf \n");
						if(m2!=NULL){
							free(m2);
							m2 = NULL;
						}
						exit(EXIT_FAILURE);
					}
				}
			}else if (ferror (stdin)){
				fprintf(stderr, "Error reading stdin\n");
				if(m2!=NULL){
					free(m2);
					m2 = NULL;
				}
				exit(EXIT_FAILURE);
			}else{
				fprintf(stderr, " Reading m2. Unknown error fscanf \n");
				if(m2!=NULL){
					free(m2);
					m2 = NULL;
				}
				exit(EXIT_FAILURE);
			}

//			int cantNumsMatriz = validoLinea(m1);
//			if(cantNumsMatriz == -1){
//				fprintf(stderr,"Linea incorrecta. %s \n", m1);
//				free(m1);
//				exit(1);
//			}
//			if(cantNumsMatriz!= (fil1*col1)){
//				fprintf(stderr,"Matriz incorrecta . %s \n", m1);
//					free(m1);
//					exit(1);
//		   }
//			cantNumsMatriz = validoLinea(m2);
//			if(cantNumsMatriz == -1){
//				fprintf(stderr,"Linea incorrecta. %s \n", m2);
//				free(m2);
//				exit(1);
//			}
//			if(cantNumsMatriz!= (fil2*col2)){
//				fprintf(stderr,"Matriz incorrecta. %s \n", m2);
//					free(m2);
//					exit(1);
//		   }


			if (col1== fil2){
				double* out = (double*) malloc(sizeof(double)*fil1*col2);
//				printf("puntero a m1 2: %p\n", m1);
//				printf("puntero a m2 2: %p\n", m2);
				multiplicarMatrices(fil1, col1, fil2, col2, m1, m2, out);
//				for(int j =0; j< fil1*col2; j++){
//					printf("OUT: %d double leido del buffer %lf \n", cantNums2, out[j]);
//				}
				bytes_consumed = 0;
				memset (buffer,0,SIZE_MAT);
				sprintf(buffer+ bytes_consumed,"%dx%d%n\n", fil1,col2, & bytes_now);
				bytes_consumed += bytes_now;
				for(int i=0;i<fil1*col2;i++){
					sprintf(buffer+ bytes_consumed," %lf%n",out[i], & bytes_now);
					bytes_consumed += bytes_now;
				}
				puts(buffer);
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


//
//
//		int cantNumsMatriz = validoLinea(m1);
//		if(cantNumsMatriz == -1){
//			fprintf(stderr,"Linea incorrecta. %s \n", m1);
//			free(m1);
//			exit(1);
//		}
//		//fgetc()
//		while (fgets(buffer, sizeof(buffer), stdin) != 0)
//		{
//		    int cantNumsMatriz = validoLinea(buffer);
//		    if(cantNumsMatriz == -1){
//		    	fprintf(stderr,"Linea incorrecta. %s \n", buffer);
//		    	free(buffer);
//		    	exit(1);
//		   }
//		    double matriz1[cantNumsMatriz];
//		    bytes_consumed = 0;
//		    sscanf(buffer+ bytes_consumed, "%d%c%d%n", &fil,&s,&col, & bytes_now);
//		    bytes_consumed += bytes_now;
//		    if(cantNumsMatriz!= (fil*col)){
//		    	fprintf(stderr,"Matriz incorrecta. %s \n", buffer);
//		    		free(buffer);
//		    		exit(1);
//		   }
//		   	for(i = 0 ; i < cantNumsMatriz; i++){
//		    	sscanf(buffer+ bytes_consumed, "%lf%n", &matriz1[i], & bytes_now);
//		    	bytes_consumed += bytes_now;
//		    }
//		    fgets(buffer, sizeof(buffer), stdin);
//		    cantNumsMatriz = validoLinea(buffer);
//		    double matriz2[cantNumsMatriz];
//		    bytes_consumed = 0;
//		    sscanf(buffer+ bytes_consumed, "%d%c%d%n", &fil2,&s,&col2, & bytes_now);
//		    bytes_consumed += bytes_now;
//		    if(cantNumsMatriz!= (fil2*col2)){
//		    	fprintf(stderr,"Matriz incorrecta. %s", buffer);
//		    	free(buffer);
//		    	exit(1);
//		    }
//		    for(i = 0 ; i < cantNumsMatriz; i++){
//		    	sscanf(buffer+ bytes_consumed, "%lf%n", &matriz2[i], & bytes_now);
//		    	bytes_consumed += bytes_now;
//		    }
//
//		    if (col== fil2){
//		    	double out[fil*col2];
//		    	multiplicarMatrices(fil, col, fil2, col2, &matriz1, &matriz2, &out);
//		    	bytes_consumed = 0;
//		    	memset (buffer,0,SIZE_MAT);
//		    	sprintf(buffer+ bytes_consumed,"%dx%d%n\n", fil,col2, & bytes_now);
//		    	bytes_consumed += bytes_now;
//		    	for(i=0;i<fil*col2;i++){
//		    		sprintf(buffer+ bytes_consumed," %lf%n",out[i], & bytes_now);
//		    		bytes_consumed += bytes_now;
//		    	}
//		    	puts(buffer);
//		    }else{
//		    	fprintf(stderr,"Matrices incorrectas para la multiplicacion. \n");
//		    	free(buffer);
//		    	exit(1);
//		    }
//		}
	}
	return 0;
}
