#include <stdio.h>

#define M 20;
#define N 20;

void show(int matrix[m][n]){
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			printf("%d",matrix[i][j]);
			if(j==m-1)
				printf("\n");
		}
}
void conv(int source[ ][ ],& int targe[ ]{
	
}
void main(){
	int arr[M][N];
	for(int i=0,i<M;i++){
		for(int j=0,j<N;j++){
			if(i>=j)
				a[i][j]=1;
			else
				a[i][i]=0;
		}
	}//for
	show(arr);
		
}