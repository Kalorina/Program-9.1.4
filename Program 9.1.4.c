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

int determinant(MAT *matica){
	int i,j;
	int fix=0;
	int det=0;
	
	if(matica->rows!=matica->cols){
		printf("Matica nieje stvorcova, nemoze byt unimodularna.");
	}
	else{
		if(matica->rows==1){
			det=matica->elem[0];
		}
		else{
			if(matica->rows==2){
				det=matica->elem[0]*matica->elem[3]-matica->elem[1]*matica->elem[2];
			}
			else{
				for(i=0;i<matica->rows;i++){
					det+=pow(-1,fix+i)*matica->elem[i]*determinant(minor(matica,fix,i));	
				}	
			}
		}
	}
	return det;
}

char mat_unimodular(MAT *mat){
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
	int det=0;
		
	ptr=create_mat(4,4);	
	print(ptr);

    MAT *min = minor(ptr, 1, 1);
//    print(min);
    
    det=determinant(ptr);
    printf("Determinant matice je: %d",det);
    
    mat_unimodular(ptr);

	free(min->elem);
	free(min);

	free(ptr->elem);
	free(ptr);
}

