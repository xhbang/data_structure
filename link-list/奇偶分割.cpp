
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//#define OVERFLOW 2
#define OK 1
#define ERROR 0

typedef int ElemType;
//typedef char ElemType;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*Linklist;

typedef int Status;

//////////////////函数声明区
Status Getelem(Linklist L,int i,ElemType e);
Status Insertlist(Linklist &L,int i,ElemType e);
Status Deletelist(Linklist L,int i,ElemType e);
void Createlist(Linklist &L,int i);
void Mergelist(Linklist La,Linklist Lb,Linklist &Lc);
void Showlist(Linklist L);
void Select(Linklist La,Linklist &Lb,Linklist &Lc);


//////////////////函数实现区
void Select(Linklist La,Linklist &Lb,Linklist &Lc){
	Linklist pa,pb,pc;
	Lb=(Linklist)malloc(sizeof(LNode));
	Lc=(Linklist)malloc(sizeof(LNode));
	pa=La->next;pb=Lb;pc=Lc;
	int i=1;
	while(pa){
		if(i%2 !=0){
			pb->next=pa;pb=pa;pa=pa->next;
		}
		else{
			pc->next=pa;pc=pa;pa=pa->next;
		}
		i++;
	}
	
}
Status Getelem(Linklist L,int i,ElemType e){
	LNode *p;
	p = L;
	int j = 0;
	while(p && j<i){
		p = p->next;
		++j;
	}
	if(!p || j>i)
		return ERROR;
	e = p->data;
	return OK;
}

Status Insertlist(Linklist &L,int i,ElemType e){
	LNode *p=L,*pn;
	int j=0;
	while(p || j<i){
		p = p->next;
		++j;
	}
	if(!p || j>i)
		return ERROR;
	pn = (Linklist)malloc(sizeof(LNode));
	pn->data = e;
	pn->next = p->next;
	p->next =pn;
	return OK;
}

Status Deletelist(Linklist L,int i,ElemType e){
	LNode *p,*q;
	p=L->next;
	int j =0;
	while(p->next && j<i-1){
		p=p->next;
		++j;
	}
	if(!(p->next) || j<i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e=q->data;
	free(q);
	return OK;
}

void Createlist(Linklist &L,int i){
	Linklist p;
	ElemType e;
	L = (Linklist)malloc(sizeof(LNode));
	L->next = NULL;
	for(;i>0;--i){
		p=(Linklist)malloc(sizeof(LNode));
		printf("enter element!\n");
		scanf("%d",&e);
		p->data=e;
		p->next = L->next;
		L->next = p;
	}
}

void Mergelist(Linklist La,Linklist Lb,Linklist &Lc){
	Linklist pa,pb,pc;
	pa = La->next;
	pb = Lb->next;
	Lc=pc=La;
	while(pa && pb){
		if(pa->data <= pb->data){
			pc->next=pa;pc=pa;pa=pa->next;
		}
		else{
			pc->next=pb;pc=pb;pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;
	free(Lb);
}

void Showlist(Linklist L){
	LNode *p=L->next;
	while(p){
		printf("%d",p->data);
		p=p->next;
	}
	printf("\n");
}

void main(){
	Linklist La,Lb,Lc,Ld,Le;
	int i;
	printf("enter the length of La:\n");
	scanf("%d",&i);
	Createlist(La,i);
//a very serious problem: the value of la cannot be changed!!
	Showlist(La);

	printf("enter the length of Lb:\n");
	scanf("%d",&i);
	Createlist(Lb,i);
	Showlist(Lb);

	Mergelist(La,Lb,Lc);
	Showlist(Lc);

	Select(Lc,Ld,Le);
	Showlist(Ld);
	Showlist(Le);

}