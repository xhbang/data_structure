//////////////////////////////
//          л�г�Ʒ        //
//          ��ӭ����        //
//       sonicode.cn        //
//////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct ElemType{
	float coef;
	int expn;
}ElemType;

typedef struct Node{
	ElemType data;
	struct Node *next;
}Node;

typedef Linklist polynomail;

///////////////////����������



////////////////////////////

void Create(polynomail *P,int m){
	Initlist(P);
	h = Gethead(P);

}