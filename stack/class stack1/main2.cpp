/*------------------------------------
二进制转换器
------------------------------------*/

#include <iostream>
#include "stack.h"

#define VALUE 2
using namespace std;

int main(){
	Stack s;
	int num;
	cout<<"enter the number u want to tranform:"<<endl;
	cin>>num;

	while(num){
		s.push(num%VALUE);
		num=num/VALUE;
	}

	cout<<"display resurt!:"<<endl;
	s.display(cout);

	cout<<"display one by one:"<<endl;
	while(!s.empty()){
		cout<<"poping:\t"<<s.top()<<endl;
		s.pop();
	}

	return 0;
}