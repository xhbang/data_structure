#include <iostream>
#include <new>
#include "SeqQueue.h"

using namespace std;

#define OK 1 
#define OVERFLOW -2 

typedef struct BinNode		
{   
	char data; 
	struct BinNode	*lchild,*rchild; 
} BinNode, *BinTree; 

void visit(BinTree *T){
	cout<<(*T)->data<<endl;
}

void level(BinTree root){
	if(root==NULL)
		cout<<"EMPTY TREE"<<endl;
	else{
		BinTree current=root;
		SeqQueue<BinTree> q;
		q.En_Queue(root);
		while(!q.Is_Empty()){
			current=q.De_Queue();
			visit(&current);
			if(current->lchild!=NULL)
				q.En_Queue(current->lchild);
			if(current->rchild!=NULL)
				q.En_Queue(current->rchild);
		}
	}
}
 
int CreateBinTree(BinTree *Tree) 
{ 
	char ch; 
	cin>>ch; 
	if(ch == '#')  
		(*Tree) = NULL; 
	else 
	{ 
		if(!((*Tree) = new BinNode))
			exit(OVERFLOW); 
		(*Tree)->data = ch; 
		CreateBinTree(&((*Tree)->lchild)); 
		CreateBinTree(&((*Tree)->rchild)); 
	} 
	return (OK);  
}/*CreateBiTree*/ 
 
int depth(BinTree T) 
{ 
	int n,n1,n2; 
	if(!T) 
		n=0; 
	else 
	{ 
		n1=depth(T->lchild); 
		n2=depth(T->rchild); 
		n=1+(n1>n2?n1:n2); 
	} 
	return n; 
} 
 
int  leaf(BinTree T) 
{ 
    int n1,n2; 
	if(!T) return 0; 
	else if((!T->lchild) &&  (!T->rchild))return 1; 
	else 
	{ 
		 n1=leaf(T->lchild); 
		 n2=leaf(T->rchild); 
		 return(n1+n2); 
	} 
} 
 
void main()		 
{   
	BinTree T=NULL; 
	printf("BEGIN\n"); 
 
	CreateBinTree(&T);			 
	cout<<"END\n"<<endl;
    cout<<"DEPTH\n"<<depth(T)<<endl;
	cout<<"LEAF\n"<<leaf(T)<<endl; 
	level(T);
} 
 


