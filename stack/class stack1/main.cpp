/*****************************
FOR TESTING
*****************************/

#include <iostream>
#include "stack.h"

using namespace std;

int main(){
	Stack s;

	int item;
	cout<<"enter num for the items"<<endl;
	cin>>item;
	while(item--)
		s.push(item);

	cout<<"DISPLAY STACK CONTENT"<<endl;
	s.display(cout);								//��һ�����ѧϰ��
	
	cout<<"stack empty?"<<s.empty()<<endl;
	cout<<"top value"<<s.top()<<endl;

	while(!s.empty()){
		cout<<"poping:\t"<<s.top()<<endl;
		s.pop();	
	}

	cout<<"top value:\n"<<s.top()<<endl;
	cout<<"trying to pop\n"<<endl;
	s.pop();

}