#include <iostream>
#include <deque>
using namespace std;


class Node{
public:
	int pos;		//-1 means it is missing or deleted
	Node*  next;

	Node()	{p=NULL;}
};

template <typename T>
class List{
private:
	deque<T> dlist;
	Node * head;
	int size;
public:
	void insert(int pos,const T&item);
	void push_back(const T&item);

	friend ostream& operator<<(ostream &out,const List<T>& L){
		for(deque<T>::iterator iter=L.dlist.begin();iter!=L.dlist.end())
	}


};

template <typename T>
void List<T>::insert(int pos,const T&item){		//第loc个后插
	Node<T> *pre,*current,*p;
	current=head->next;
	pre=head;
	if(pos<1 || pos>size){
		cout<<"ERROR in range"<<endl;
		throw out_of_range;		//抛出错误类型
	}
	for(int i=0;i<pos;i++){
		pre=pre->next();
	}
	current=pre->next();
	p= new Node<T>;
	cin>>p->pos;

	pre->next=p;
	
}