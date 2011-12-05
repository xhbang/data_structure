#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define STACK_INIT 100;
#define INCRESEMENT 20;

typedef int ElemType;
typedef int Status;
//typedef char ElemType;

typedef struct{
	ElemType *top;
	ElemType *base;
	int stacksize;
}Stack;

#define ERROR 1;
#define OK 0;
#define OVERFLOW 2;

Status Initstack(Stack &S);
Status Destroystack(Stack &S);
Status Clearstack(Stack &S);
Status Isempty(Stack S);
int Stacklength(Stack S);
Status Gettop(Stack S,ElemType &e);
Status Pop(Stack &S,ElemType &e);
Status Push(Stack &S,ElemType e);
//Status Visit(Stack S); 

Status Initstack(Stack &S){
	S.base = (ElemType *)malloc(STACK_INIT * sizeof(ElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT;
	return OK;
}//init

Status Gettop(Stack S){
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;
}//gettop

Status Pop(Stack &S,ElemType &e){
	if(S.top==S.base)
		return ERROR;
	e = *--S.top;
	return OK;
}

Status Push(Stack &S,ElemType e){
	if(S.top-S.base >=S.stacksize){
		S.base = (ElemType *)relloc(S.base,(STACK_INIT+INCRESEMENT)*sizeof(ElemType));
		if(!S.base)
			exit(OVERFLOW);
		S.stacksize+=INCRESEMENT;
	}
	S.top++ = e;
	return OK;
}

Status Isempty(Stack S){
	if(S.top==S.base)
		return 1;
	else
		return 0;
}

void conversion(Stack &S){
	Initstack(S);
	printf("")
	
}