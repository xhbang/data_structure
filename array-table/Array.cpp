/*-------------------------------------------
数组的表示：顺序
使用变长参数列表
--------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>		//后面的va_list macro

typedef int Status;
typedef int ElemType;

#define MAX_DIM 8			//定义最大维
#define OK 1
#define ERROR 0

//-------------------顺序储存表示---------------
typedef struct Arrray{
	int dim;		//维度
	ElemType *base;
	int * bounds;			//数组维界基址
	int *constants;			//映像函数常量
}Array;

/*----------------
初始化
-----------------*/
void Init(Array &A,int dim,...){			//使用变长参数列表
	va_list ap;
	if(dim<1 || dim > MAX_DIM)
		exit(1);			//维度越界
	A.dim=dim;
	A.bounds=(int *)malloc(dim*sizeof(int));
	if(!A.bounds)
		exit(1);
	int elemtotal=1,i;		//A的元素总数是elemtotal

//	va_list ap; ap的类型是储存变长参数列表的数组
	va_start(ap,dim);
	for(i=0;i<dim;i++){
		A.bounds[i]=va_arg(ap,int);
		if(A.bounds[i]<0)
			exit(1);
		elemtotal*=A.bounds[i];
	}
	va_end(ap);

	A.base=(ElemType * )malloc(elemtotal*sizeof(ElemType));
	if(!A.base)
		exit(1);

	A.constants=(int *)malloc(dim*sizeof(int));
	if(!A.constants)
		exit(1);

	A.constants[dim-1]=1;			//用来计算N维数组元素储存位置的中间值:0~dim-1
	for(i=dim-2;i>=0;--i)
		A.constants[i]=A.bounds[i+1]*A.constants[i+1];
}

void Destroy(Array& A){		//检验三个指针+FREE
	if(!A.base)
		exit(1);
	free(A.base);A.base=NULL;

	if(!A.bounds)
		exit(1);
	free(A.bounds);A.bounds=NULL;

	if(!A.constants)
		exit(1);
	free(A.constants);A.constants=NULL;
}

Status Locate(Array A,va_list ap,int &off){
	off=0;
	for(int i=0;i<A.dim;i++){
		int ind=va_arg(ap,int);
		if(ind<0 || ind>MAX_DIM)
			return ERROR;
		off+=A.constants[i]*ind;
	}
	return OK;
}

Status Value(Array A,ElemType &e,...){
	va_list ap;
	va_start(ap,e);				
	int off=0,result;
	if(result=Locate(A,ap,off)==ERROR)
		return result;		//既ERROR
	e=*(A.base+off);
	return OK;
} 

Status Assign(Array &A,ElemType e,...){
	va_list ap;
	va_start(ap,e);
	int off=0,result;
	if(result=Locate(A,ap,off)==ERROR)
		return result;
	*(A.base+off)=e;
	return OK;
}

//测试用主函数
void main(){
	Array myArray;
	int i,j,k,_dim=3,dim1=5,dim2=4,dim3=3;
	int val=2;
	Init(myArray,_dim,dim1,dim2,dim3);
	for(i=0;i<dim1;i++)
		for(j=0;j<dim2;j++)
			for(k=0;k<dim3;k++)
				Assign(myArray,val,i,j,k);

	for(i=0;i<dim1;i++){
		for(j=0;j<dim2;j++){
			for(k=0;k<dim3;k++){
				Value(myArray,val,i,j,k);
				printf("%d ",val);
			}//for
			printf("\n");
		}//for
		printf("\n");
	}//for
}