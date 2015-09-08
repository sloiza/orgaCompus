#include "tp0.h"

/**
VALIDAR QUE NO SEAN CARACTERES
SI ES ARCHIVO VACIO IMPRIMIR POR STDERR
**/


extern int errno ;


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
			&& (((strcmp(argumentos[1], "-V") == 0))
					|| (strcmp(argumentos[1], "--version") == 0) || (strcmp(argumentos[1], "-v") == 0))) {
		printf("Version 1.0\n");
		retorno = 0;
	}

	return retorno;
}

int validoLinea(char *linea){
	int desp =0;
	char fil = *(linea+desp);
	desp++;
	if( fil<'0' || fil > '9') printf ("%c", c);
	char x = *(linea+desp);
	desp++;
	if(!((x=='x') || (x=='X'))) printf("%c", x);
	char col = *(linea+desp);
	desp++;
	if( col<'0' || col > '9') printf ("%c", c2);

	int cantNums = 0;
	char car =*(linea+desp);
	desp++;
	while(car!= '\n'){
		if(car == ' ') {
			cantNums++;
			car =*(linea+desp);
			desp++
		}else{
			if( (car>='0' && car <= '9') || (car =='.')){
				car =*(linea+desp);
				desp++
			}else{
				printf("ERROR");
				return -1;
			}
		}

	}

}


 int main(int argc, char *argv[])
{
	if (!checkArguments(argc,argv)){
		return 1;
	}else{

		char *buffer= NULL;

		int read = 0;
		size_t len =0;
		char s;
		int fil=0 ,col=0, i, j,k, fil2=0, col2=0, bytes_now=0;
		int bytes_consumed = 0;
		read = getline(&buffer, &len, stdin);
		validoLinea(buffer);
		if(read == -1){
			//No recibio stream de entrada
			printf("No stdin \n");
		}

		while(-1 != read){

			bytes_consumed = 0;
			sscanf(buffer+ bytes_consumed, "%d%c%d%n", &fil,&s,&col, & bytes_now);
			bytes_consumed += bytes_now;
			printf("\n%d%c%d", fil,s,col); //BORRAR DESPUES
			printf("\n tipo fil: %d\n tipo col: %d\n", sizeof(fil),sizeof(col));
			double matriz1[fil][col];
			for(i=0; i<fil;i++){
				for(j=0;j<col;j++){
				sscanf(buffer+ bytes_consumed, "%lf%n", &matriz1[i][j], & bytes_now);
				bytes_consumed += bytes_now;
				 printf("%lf", matriz1[i][j]); //BORRAR DESPUES
				 printf("\n tipo float: %d\n ", sizeof(matriz1[i][j]));
				}
			}

			memset (buffer,0,SIZE_MAT);
			read = getline(&buffer, &len, stdin);
			bytes_consumed = 0;
			sscanf(buffer+ bytes_consumed, "%d%c%d%n", &fil2,&s,&col2, & bytes_now);
			bytes_consumed += bytes_now;
			printf("\n %d%c%d", fil2,s,col2);
			double matriz2[fil2][col2];
			for(i=0; i<fil2;i++){
				for(j=0;j<col2;j++){
					sscanf(buffer+ bytes_consumed, "%lf%n", &matriz2[i][j], & bytes_now);
					bytes_consumed += bytes_now;
					printf("%lf", matriz2[i][j]);
				}
			}
			if (col== fil2){

				double sum;
				double out[fil][col2];
				for(i=0;i<fil;i++){ // fila de matriz 1
					for(j=0;j<col2;j++){  // columna de segunda matriz
						sum=0;
						for(k=0;k<col;k++)
							sum=sum+matriz1[i][k]*matriz2[k][j];
							out[i][j]=sum;
					}
				}
				printf("\n Matriz resultado \n");  //BORRAR DESPUES
				bytes_consumed = 0;

				memset (buffer,0,SIZE_MAT);
				sprintf(buffer+ bytes_consumed,"%dx%d%n\n", fil,col2, & bytes_now);
				bytes_consumed += bytes_now;
				for(i=0;i<fil;i++){
					for(j=0;j<col2;j++){
						sprintf(buffer+ bytes_consumed," %lf%n",out[i][j], & bytes_now);
						bytes_consumed += bytes_now;
					}
				}
				puts(buffer);
			}else{
				printf("matriz incorrecta para la multiplicacion"); //MANEJO STDERR
				return 0; // escribir error en archivo
			}
			memset (buffer,0,SIZE_MAT);
			read = getline(&buffer, &len, stdin);

		}

		//printf("\n Size read: %d\n Len: %d\n", read, len); //BORRAR DESPUES

		free(buffer);
		return 0;
	}
}



// int multiplyByInput(){
// 	int a[5][5],b[5][5],c[5][5],i,j,k,sum=0,m,n,o,p;
// 	printf("\nEnter the row and column of first matrix");
// 	scanf("%d %d",&m,&n);
// 	printf("\nEnter the row and column of second matrix");
// 	scanf("%d %d",&o,&p);
// 	if(n!=o){
// 		printf("Matrix mutiplication is not possible");
// 		printf("\nColumn of first matrix must be same as row of second matrix");
// 	}else{
// 	  printf("\nEnter the First matrix->");
// 	  for(i=0;i<m;i++)
// 		  for(j=0;j<n;j++)
// 			  scanf("%d",&a[i][j]);
// 	  printf("\nEnter the Second matrix->");
// 	  for(i=0;i<o;i++)
// 		  for(j=0;j<p;j++)
// 			  scanf("%d",&b[i][j]);
// 	  printf("\nThe First matrix is\n");
// 	  for(i=0;i<m;i++){
// 	  printf("\n");
// 	  for(j=0;j<n;j++){
// 		   printf("%d\t",a[i][j]);
// 	  }
// 	  }
// 	  printf("\nThe Second matrix is\n");
// 	  for(i=0;i<o;i++){
// 		  printf("\n");
// 		  for(j=0;j<p;j++){
// 			  printf("%d\t",b[i][j]);
// 		  }
// 	  }
// 	  for(i=0;i<m;i++)
// 		  for(j=0;j<p;j++)
// 		   c[i][j]=0;
// 	  for(i=0;i<m;i++){ //row of first matrix
// 		  for(j=0;j<p;j++){  //column of second matrix
// 			   sum=0;
// 			   for(k=0;k<n;k++)
// 				   sum=sum+a[i][k]*b[k][j];
// 			   c[i][j]=sum;
// 		  }
// 	  }
// 	}
// 	printf("\nThe multiplication of two matrix is\n");
// 	for(i=0;i<m;i++){
// 	  printf("\n");
// 	  for(j=0;j<p;j++){
// 		   printf("%d\t",c[i][j]);
// 	  }
// 	}
// 	return 0;
// }

// int main(int argc, char* argv[]){
// //	 int errnum;
// //	   if (pf == NULL)
// //	   {
// //	      errnum = errno;
// //	      fprintf(stderr, "Value of errno: %d\n", errno);
// //	      perror("Error printed by perror");
// //	      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
// //	   }
// //
// 	if (!checkArguments(argc,argv)){
// 		return 0;
// 	}else{
// 		//Datos a obtener de stdin

// 		double v1[6] = {1.0, 3.0, 2.0, 4.0, 1.0, 2.0};
// 		double v2[6] = {4.0, 1.0, 3.0, 5.0, 1.0, 2.0};
// 		int f1= 2;
// 		int c1= 3;
// 		int f2= 3;
// 		int c2= 2;
// 		//Fin datos a obtener de stdin
// 		double m1[f1][c1];
// 		double m2[f2][c2];
// 		multiplicarMatrices(v1,f1,c1,v2,f2,c2,m1,m2);

// 		return 0;
// 		// proceso
// 		//return 1;
// 	}

// }





