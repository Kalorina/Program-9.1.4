#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	unsigned int rows;
	unsigned int cols; 
	float *elem;
}MAT;


MAT* mat_create_with_type(unsigned int rows, unsigned int cols){
	MAT *mat;
	
	mat = (MAT*) malloc(sizeof(MAT));
	mat->rows=rows;
	mat->cols=cols;
	mat->elem = (float*) malloc((rows*cols) * sizeof(float));
	
	if( mat == NULL ){
		return (void *)1;
	}
	
	if(mat->elem == NULL){
		return (void *)1;
	}
	
	return mat;
}

void mat_print(MAT *mat){
	int i,j;
	
	for(i=0;i<mat->rows;i++){
		for(j=0;j<mat->cols;j++){
			printf("%.1f ", mat->elem[mat->cols*i+j]);
		}
		printf("\n");
	}
}

void mat_unit(MAT *mat){
	int i,j;
	
	for(i=0;i<mat->rows;i++){
		for(j=0;j<mat->cols;j++){
			if(i==j){
				mat->elem[mat->cols*i+j]=1;	
			}
			else{
				mat->elem[mat->cols*i+j]=0;	
			}
		}
	}
	
}

void mat_random(MAT *mat){
 	int i,n;
	n=mat->rows*mat->cols;
	for(i=0;i<n;i++){
		mat->elem[i]=rand()%3-1;
	}
 }

MAT* mat_minor(MAT *mat, unsigned int x, unsigned int y){
	int i,j;
	int min_i, min_j;
	MAT *min;
	
	min = mat_create_with_type(mat->rows-1,mat->cols-1);
	
	for(i=0;i<mat->rows;i++){
		if (i<x){
			min_i=i;
		} 
		else if (i==x) continue;
		else {min_i=i-1;}
		for(j=0;j<mat->cols;j++){
			if (j<y) {
				min_j=j;
			}
			else if(j==y) continue;
			else {min_j=j-1;}
			
			min->elem[(mat->cols-1)*min_i+min_j]=mat->elem[mat->cols*i+j];
		}
	}

	return min;	
}

int determinant(MAT *mat){
	int i,j;
	int fix=0;
	int det=0;
	
	if(mat->rows!=mat->cols){
		return 1;
	}
	else{
		if(mat->rows==1){
			det=mat->elem[0];
		}
		else{
			if(mat->rows==2){
				det = mat->elem[0]*mat->elem[3]-mat->elem[1]*mat->elem[2];
			}
			else{
				for(i=0;i<mat->rows;i++){
					det += pow(-1,fix+i)*mat->elem[i]*determinant(mat_minor(mat,fix,i));	
				}	
			}
		}
	}
	return det;
}

char mat_create_random_unimodular(MAT *mat){
	int i,n;
	n=mat->rows*mat->cols;
	for(i=0;i<n;i++){
		mat->elem[i]=rand()%3-1;
	}
	
	int det=0;
	det=determinant(mat);
	
	if(det==1){
		return 0;
	}
	else{
		if(det==-1){
			return 0;
		}
		else{
			return 1;
		}
	}
}
 
main(){
	
	MAT *ptr;
	char vystup=0;
		
	ptr = mat_create_with_type(5,5);	
    vystup=mat_create_random_unimodular(ptr); 
	mat_print(ptr);
	
	if(vystup==0){
		printf("Matica je unimodularna.");
	} 
	else if(vystup==1){
		printf("Matica nie je unimodularna.");
	}
	else {
		printf("Error.");
	}
	
	free(ptr->elem);
	free(ptr);

}

