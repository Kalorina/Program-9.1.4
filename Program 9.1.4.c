#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	unsigned int rows;
	unsigned int cols; 
	float *elem;
}MAT;

/* *elem = makro*/ 

MAT* create_mat(unsigned int rows, unsigned int cols){
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
			printf("%.1f ", matica->elem[matica->cols*i+j]);
		}
		printf("\n");
	}
}

MAT* minor(MAT *matica, unsigned int x, unsigned int y){
	int i,j;
	int min_i, min_j;
	MAT *min;
	
	min = create_mat(matica->rows-1,matica->cols-1);
	
	for(i=0;i<matica->rows;i++){
		if (i<x){
			min_i=i;
		} 
		else if (i==x) continue;
		else {min_i=i-1;}
		for(j=0;j<matica->cols;j++){
			if (j<y) {
				min_j=j;
			}
			else if(j==y) continue;
			else {min_j=j-1;}
			
			min->elem[(matica->cols-1)*min_i+min_j]=matica->elem[matica->cols*i+j];
		}
	}

	return min;	
}

 
main(){
	
	MAT *ptr;
		
	ptr=create_mat(4,4);	
	print(ptr);

    MAT *min = minor(ptr, 1, 1);
    print(min);

	free(min->elem);
	free(min);

	free(ptr->elem);
	free(ptr);
}

