#ifndef BITREE_CLASS
#define BITREE_CLASS
#include<iostream>
using namespace std;

struct BiNode{
	char data;
	BiNode* Lchild;
	BiNode* Rchild;
};

class BiTree{
private:
	BiNode *top;
public:
	void creatBiTree();
	void creat(BiNode* t);
	
	void printBiTree();
	void print(BiNode* t);
};
void BiTree::creatBiTree(){
	creat(top);	
}
void BiTree::creat(BiNode* t){
	char ch;
	cin>>ch;
	if(ch=='#')
		t=0;
	else
	{	t=new  BiNode;
		t->data=ch;
		creat(t->Lchild);
		creat(t->Rchild);
	}
}
void BiTree::printBiTree(){
	print(top);
}
void BiTree::print(BiNode *t){
	if(t){
		cout<<t->data;
		print(t->Lchild);
		print(t->Rchild);
	}
}
#endif
