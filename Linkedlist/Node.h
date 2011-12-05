#ifndef NODE
#define NODE
#include<iostream>
using namespace std;

template<class T>
class Node{
private:
	Node<T>* next;
	T data;
public:
	Node(const T& data,Node<T>* next=0);
	Node()	{next=0;};

	void InsertAfter(Node<T>* p);
	Node<T>* DeleteAfter();
	Node<T>* NextNode() const;
	T& GetData();
	void SetData(T& data);
};

template<class T>
Node<T>::Node( const T& dat,Node<T>* nxt=0):data(dat),next(nxt)
{}
template<class T>
void Node<T>::InsertAfter(Node<T> *p){			//在P后插入
	p->next=next;
	next=p;
}
template<class T>
Node<T>* Node<T>::DeleteAfter(){
	Node<T>* p;
	p=next;
	if(!p->next)
	{	next=0;
		return 0;
	}
	next=next->next;
	return p;
}
template<class T>
Node<T>* Node<T>::NextNode() const{		//返回下一节点
	return next;
}
template<class T>
void Node<T>::SetData(T& data){
	this->data=data;
}
template<class T>
T& Node<T>::GetData(){		//返回数据
	return data;
}

#endif
