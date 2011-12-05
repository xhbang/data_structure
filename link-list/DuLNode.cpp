#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef int ElemType;
typedef int Status;

typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode,*DuLinklist;

///////////////////define
Status Insert(DuLinklist L,int i,ElemType e);
Status Delete(DuLinklist L,int i,ElemType e);
Dulinklist Getelem(DuLinklist L,int i);

///////////////////implement
Status Insert(DuLinklist L,int i,ElemType e){
	DuLNode *p,*q;
	if(!(q=Getelem(L,i)))

//i的有效范围：>1 <length+1
	if(!(p=((DuLinklist)malloc(sizeof(DuLNode))))
		return ERROR;
	p->data = e;
//特别注意顺序
	p->prior = q->prior;
	p->next = q;
	q->prior->next = p;
	q->prior =p;
	return OK;
}

Status Delete(DuLinklist L,int i,ElemType e){
	DuLNode *p;
	if(!(p=Getelem(L,i)))
		return ERROR;
	e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p);
	return OK;
}

DuLinklist Getelem(DuLinklist L,int i){
	DuLNode *p;
	p=L;
	int j=0;
	while(p && j<i){
		p=p->next;
		++j;
	}
	return p;
}