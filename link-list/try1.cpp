//////////////////////////////
//          谢行出品        //
//          欢迎盗版        //
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

///////////////////函数声明区



////////////////////////////

void Create(polynomail *P,int m){
	Initlist(P);
	h = Gethead(P);

}