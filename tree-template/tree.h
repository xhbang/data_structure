#ifndef treenode_H
#define treenode_H

static index(0);              //创建数的时候计算创建的个数，用以与数组元素个数比较。

#include <iostream>
using namespace std;

//*******************************
template <class T>
class tree;                                 //声明两个类都是模版型。
template <class T>
class treenode;
//*******************************

//****************************************************
//class defination:


template <class T>
class tree{
private:
	treenode<T> *root;
	T refvalue;

public:
	tree() : root(NULL), refvalue(-1){};
    tree(const T &item) : refvalue(item), root(NULL){};
    tree(const tree<T> &bt);
	virtual void create(T date[], int number);
    virtual void traverse();
    virtual int heigth();
    virtual int size();
	~tree(){destory(root);};

protected:
	void destory(treenode<T> * pstart);
	void postorder(treenode<T> * p);
	void preorder(treenode<T> * p);
	void inorder(treenode<T> * p);
	int counth(treenode<T> * pstart);
	int counts(treenode<T> * pstart);
	int max(int x, int y);
	void createstep(treenode<T> * pstart, T data[], int num);
	treenode<T> * copy(treenode<T> * pstart);

};



template <class T>
class treenode{
private:
	friend class tree<T>;

public:
	T data;
	treenode<T> *lchild, *rchild;
	
	treenode(): lchild(NULL), rchild(NULL){};
	treenode(T i) : data(i), lchild(NULL), rchild(NULL){}; 

};


//********************************************************************
//public function:


template <class T>
tree<T> :: tree( const tree<T> &t )                //copy a tree
{
	root = copy(t.root);
}

template <class T>
treenode<T> * tree<T> :: copy(treenode<T> *pstart)
{
    if (pstart == NULL) return NULL;
    treenode<T> *ptemp = new treenode<T>;   // allocate a treenode
    ptemp->data = pstart->data;               // copy data field of node
    ptemp->lchild = copy(pstart->lchild); // copy the leftchild of the node
    ptemp->rchild = copy(pstart->rchild);// copy the rightchild of the node
    return ptemp;
}



template <class T>                                      //创建。
void tree<T> :: create(T data[], int number){
    if (root == NULL) root = new treenode<T>;
    createstep(root, data, number);           //creat.cas it need argument.
		
}


template <class T>
void tree<T>::traverse(){	
	while(1){
		cout<<"选择1：前序    2：中序    3：后序    4:退出。"<<endl;
		int i=0;
		cin>>i;
		if(i < 1 || i>3)
			return;
		switch(i){
		case 1:preorder(root);
				cout<<endl;
				break;
		case 2:inorder(root);
				cout<<endl;	
				break;
		case 3:postorder(root);
				cout<<endl;	
				break;
		default:
				break;
		}
	}
}


template <class T>                          //高度
int tree<T>::heigth(){return counth(root);}

template <class T>
int tree<T>::size()                         //结点个数
{
	return counts(root);
}


//***********************************************************
//protected function:


template <class T>
int tree<T>::counts(treenode<T> *pstart)
{
	if (pstart == NULL) return 0;
    return(1 + counts(pstart->lchild) + \
		counts(pstart->rchild));
}


template <class T>                   
int tree<T>::max(int x, int y){return (x >= y) ? x : y;}


template <class T>                          //计算高度
int tree<T>::counth(treenode<T> *pstart){
	if (pstart == NULL) return 0;
    else
       return (1 + max(counth(pstart->lchild),counth(pstart->rchild)));
}

template <class T>                         //后序
void tree<T>::postorder(treenode<T> * p){
    if (p != NULL)
    {
       postorder(p->lchild);
       postorder(p->rchild);
       cout<<p->data<<"   ";
    }
}

template <class T>                         //中序。
void tree<T>::inorder(treenode<T> * p){
    if (p != NULL)
    {
       inorder(p->lchild);
       cout<<p->data<<"   ";
       inorder(p->rchild);
    }
}


template <class T>                         //前序
void tree<T>::preorder(treenode<T> * p){
    if (p != NULL)
    {
       cout<<p->data<<"   ";
       preorder(p->lchild);
       preorder(p->rchild);
    }
}

template <class T>
void tree<T>::destory(treenode<T> *pstart)
{
	if (pstart != NULL)
    {
       destory(pstart->lchild);
       destory(pstart->rchild);
       delete pstart;
    }
}

#define check(x) \
    if (data[index] != refvalue) pstart->x = new treenode<T>; \
    else pstart->x = NULL;                    //too long.


template <class T>
void tree<T>::createstep(treenode<T> *pstart, T data[], int num){
	if (pstart != NULL)
		pstart->data = data[index];
    index++;
    if (index >= num) return;
    if (pstart != NULL)
    {
       check(lchild);                            
       createstep(pstart->lchild, data, num);   //the * get the value.
       check(rchild)
       createstep(pstart->rchild, data, num);//类似栈，先将左边以栈的形式输入，
    }             //退回的时候在赋右边。需要理解的是：正面进行的时候是左边赋值
}                 //退回的时候是右边赋值。






#endif
