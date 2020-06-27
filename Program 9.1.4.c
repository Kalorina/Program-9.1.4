#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	unsigned int rows;
	unsigned int cols; 
	float *elem;
}MAT;

/* *elem = makro*/ 

MAT* matica(unsigned int rows, unsigned int cols){
	MAT *matica;
	
	/*(*matica).elem = matica->elem*/
	matica = (MAT*) malloc(sizeof(MAT));
	matica->rows=rows;
	matica->cols=cols;
	matica->elem = (float*) malloc((rows*cols) * sizeof(float));
	
	int i,n;
	n=rows*cols;
	for(i=0;i<n;i++){
		matica->elem[i]=rand()%9+1;
	}

	return matica;
}

void print(MAT *matica){
	int i,j;
	
	for(i=0;i<matica->rows;i++){
		for(j=0;j<matica->cols;j++){
			printf("%f", matica->elem[matica->cols*i+j]);
		}
	}
}

 
main(){

}

