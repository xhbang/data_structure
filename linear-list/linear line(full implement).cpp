#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define INITSIZE 100
#define INCRESE 10
#define OVERFLOW 2
#define ERROR 0
#define OK 1

typedef int Status;
//typedef int ElemType
typedef int ElemType;

typedef struct Sqlist{
	ElemType *elem;
	int length;
	int listsize;
}Sqlist;

//函数声明部分
Status Initlist(Sqlist* L);
Status Insertlist(Sqlist* L,int i,ElemType e);
Status Mergelist(Sqlist La,Sqlist Lb,Sqlist* Lc);
Status Showlist(Sqlist* L);


Status Mergelist(Sqlist La,Sqlist Lb,Sqlist* Lc){
	ElemType *pa=La.elem,*pb=Lb.elem,*pc;
	ElemType *pa_last=La.elem+La.length-1,*pb_last=Lb.elem+Lb.length-1;
	Lc->listsize=Lc->length=La.length + Lb.length;
	pc=Lc->elem=(ElemType *)malloc(Lc->listsize*sizeof(ElemType));
	if(!pc)
		return OVERFLOW;
	while(pa<=pa_last && pb<=pb_last)
//		*pc++ = (*pa++<=*pb++?*pa++:*pb++);
//another choice
	if(*pa<=*pb)
		*pc++=*pa++;
	else
		*pc++=*pb++;

	while(pa<=pa_last)
		*pc++=*pa++;
	while(pb<=pb_last)
		*pc++=*pb++;

	return OK;
}

Status Initlist(Sqlist* L){
	L->elem = (ElemType*)malloc(INITSIZE*sizeof(ElemType));
	if(!L->elem)
		return OVERFLOW;
	L->length = 0;
	L->listsize = INITSIZE;
	return OK;
}

Status Showlist(Sqlist* L){
	int i=0;
	ElemType num=0;
	for(;i<L->length;i++){
		num = L->elem[i];
		printf("%d",num);
	}
	printf("\t");

	return OK;
}

Status Insertlist(Sqlist* L,int i,ElemType e){
	if(i<1 ||i>L->length+1)
		return ERROR;
	if(L->length >L->listsize){
		ElemType *newbase;
		newbase = (ElemType*)realloc(L->elem,(L->listsize+INCRESE)*sizeof(ElemType));
		L->elem = newbase;
		L->length += INCRESE;
	}
	ElemType *p,*q;
	q = &(L->elem[i-1]);
	for(p=&(L->elem[L->length-1]);p>=q;--p)
		*(p+1)=*p;
	*q = e;
	++L->length;
	return OK;
}




int main(){
	Sqlist La,Lb,Lc;
	int i=1;
	ElemType num = 0;

	Initlist(&La);
	Initlist(&Lb);
	
	printf("plsase input LIST A,-1 to end\n");
	while(1){
		scanf("%d",&num);
		if(num == -1)
			break;
		Insertlist(&La,i,num);
		i++;
	}
	Showlist(&La);

	i = 1;
	printf("please input LIST B,-1 to end\n");
	while(1){
		scanf("%d",&num);
		if(num == -1)
			break;
		Insertlist(&Lb,i,num);
		i++;
	}
	Showlist(&Lb);

	Mergelist(La,Lb,&Lc);
	printf("MERGE DONE!\n");
	Showlist(&Lc);
	return 0;
}
