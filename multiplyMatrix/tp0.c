
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
// 	int pos = 0;
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


int validoLinea(char *linea){

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
		char s;
		int fil=0 ,col=0, i =0, fil2=0, col2=0, bytes_now=0;
		int bytes_consumed = 0;
		char buffer[BUFSIZ];
		while (fgets(buffer, sizeof(buffer), stdin) != 0)
		{
		    int cantNumsMatriz = validoLinea(buffer);
		    if(cantNumsMatriz == -1){
		    	fprintf(stderr,"Linea incorrecta. %s \n", buffer);
		    	free(buffer);
		    	exit(1);
		   }
		    double matriz1[cantNumsMatriz];
		    bytes_consumed = 0;
		    sscanf(buffer+ bytes_consumed, "%d%c%d%n", &fil,&s,&col, & bytes_now);
		    bytes_consumed += bytes_now;
		    if(cantNumsMatriz!= (fil*col)){
		    	fprintf(stderr,"Matriz incorrecta. %s \n", buffer);
		    		free(buffer);
		    		exit(1);
		   }
		   	for(i = 0 ; i < cantNumsMatriz; i++){
		    	sscanf(buffer+ bytes_consumed, "%lf%n", &matriz1[i], & bytes_now);
		    	bytes_consumed += bytes_now;
		    }
		    fgets(buffer, sizeof(buffer), stdin);
		    cantNumsMatriz = validoLinea(buffer);
		    double matriz2[cantNumsMatriz];
		    bytes_consumed = 0;
		    sscanf(buffer+ bytes_consumed, "%d%c%d%n", &fil2,&s,&col2, & bytes_now);
		    bytes_consumed += bytes_now;
		    if(cantNumsMatriz!= (fil2*col2)){
		    	fprintf(stderr,"Matriz incorrecta. %s", buffer);
		    	free(buffer);
		    	exit(1);
		    }
		    for(i = 0 ; i < cantNumsMatriz; i++){
		    	sscanf(buffer+ bytes_consumed, "%lf%n", &matriz2[i], & bytes_now);
		    	bytes_consumed += bytes_now;
		    }

		    if (col== fil2){
		    	double out[fil*col2];
		    	multiplicarMatrices(fil, col, fil2, col2, &matriz1, &matriz2, &out);
		    	bytes_consumed = 0;
		    	memset (buffer,0,SIZE_MAT);
		    	sprintf(buffer+ bytes_consumed,"%dx%d%n\n", fil,col2, & bytes_now);
		    	bytes_consumed += bytes_now;
		    	for(i=0;i<fil*col2;i++){
		    		sprintf(buffer+ bytes_consumed," %lf%n",out[i], & bytes_now);
		    		bytes_consumed += bytes_now;
		    	}
		    	puts(buffer);
		    }else{
		    	fprintf(stderr,"Matrices incorrectas para la multiplicacion. \n");
		    	free(buffer);
		    	exit(1);
		    }
		}
	}
	return 0;
}
