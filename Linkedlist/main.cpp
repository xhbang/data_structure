#include"LinkedList.h"
#include"Node.h"
#include<iostream>
using namespace std;
void main(){
	LinkedList<int> l1;
	int i=3;
	l1.InsertAt(4);
	l1.InsertAt(3);
	l1.InsertAt(2);
	l1.InsertAt(1);
	cout<<endl<<l1.ListSize()<<endl;
	l1.Print();
	LinkedList<int> l2(l1);
	cout<<endl<<l2.ListSize()<<endl;
	l2.Print();
	cout<<endl;
	cout<<l2.Find(i)<<endl;
	cout<<l2;
	cout<<"size="<<l2.ListSize()<<endl;
	l2.Reset(20);
	l2.InsertLoc(i,2);
	l2.InsertLoc(i,3);
	l2.InsertLoc(i,4);
	cout<<"size="<<l2.ListSize()<<endl;
	l2.InsertLoc(i,20);
	cout<<l2<<endl<<l1;



}






