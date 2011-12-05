#include<iostream>
using namespace std;

template<class Telem>
class List
{
public:
	void clear();
	int leng();
	Telem gete(int i);
	int loc(Telem& el);
	bool inst(int loc,Telem& el);
	Telem dele(int loc);
	bool full();
	bool empt();
};

template <class Telem> class  LinkList;
template <class Telem> class Node

{ 
	friend class  LinkList <Telem>;
	Telem data;
	Node <Telem> *next;
public:
	Node(Telem d=0,Node <Telem> *n=NULL):data(d),next(n){};
};

template <class Telem>
class  LinkList :public List<Telem>
{ 
private:
	Node <Telem> *head;
public:
		 LinkList(){ head=new Node <Telem>();};
		 LinkList(Telem a[],int n);
		 ~LinkList(){delete[] head;};
		 void init() { delete[] head; head=new Node <Telem>();};
		 Telem gete(int i);
		 int leng();
		 int loct (Telem& el);
		 bool inst (int loc,Telem& el);
		 void dele(int i);
		 bool full(){return false;};
		 bool empt(){return head->next==NULL;};
}; 

template <class Telem> 
LinkList<Telem>::LinkList(Telem a[],int n)
{
	Node <Telem> *p;
	int i;
	head=new Node <Telem>(); 
	head->next=NULL;
	for (i=n-1;i>=0;i--  )
	{
		p=new Node <Telem>();
		p->data=a[i];
		p->next= head->next;
		head->next=p;
	}
};

template <class Telem> Telem LinkList<Telem>::gete(int i)
{
	Node <Telem> *p;  
	int j;
	p= head;  
	j=0;
	while ((p!=NULL ) && (j<i))
	{p=p->next; 
	j=j+1;
	}
	if ((p!=NULL ) && (j==i))  
//	cout<<p->data<<" "; 
	return p->data;
};

template <class Telem> int LinkList<Telem>::loct(Telem& el)
{
	Node <Telem> *p;
	int j;  
	Telem data;
   p= head->next; 
	j=1;
   while (p!=NULL )
	{ 
		data=p->data;
		if (data==el) break;
		p=p->next; 
		j=j+1;
	};
   if (p!=NULL )  return(j); else return(0);
};

template <class Telem>
bool LinkList<Telem>::inst(int loc,Telem& el)
{
	Node <Telem> *p,*s;int j;
	p= head;  j=0;
	while ((p!=NULL ) && (j<loc-1))
		{ p=p->next;j=j+1;
		};
	if ((p!=NULL )&& (j==loc-1))
		{ 
			s=new Node <Telem>();
			s->data=el;
			s->next=p->next;
			p->next=s;
			return true;
		}
	else  
		return false;
};

template <class Telem> 
void LinkList<Telem>::dele(int i)
{
	Node <Telem> *p,*q; int j;char el;
	p= head;  j=0;
	while ((p->next!=NULL ) && (j<i-1))
		{ p=p->next;j=j+1;
		};
	if ((p->next!=NULL )&&(j==i-1))
	{
		q=p->next;
		p->next=p->next->next;
		el=q->data;
		delete(q);
		cout<<el<<endl;
	}  
	else 
	cout<<"not find"<<endl;
};

int main()
{
	int a[]={1,2,3,4,5,6,7,8};
	LinkList<int> ll(a,8);
	int loc=4;
	int el=9;
	ll.inst(loc,el);
	ll.dele(5);
	for(int i=1;i<=8;i++)
	ll.gete(i);
	system("pause");
	return 0;
} 