#include <iostream>
#include "stack.h"

using namespace std;

int main(){
	cout<<"enter capacities!\n";
	int cap;
	cin>>cap;
	Stack s(cap);

	cout<<"is stack empty?\t"<<s.empty()<<endl;
	
	cout<<"enter the num of element!\n";
	int num;
	cin>>num;
	while(num){
		s.push(num--*100);
	}

	cout<<"display resurt!:"<<endl;
	s.display(cout);

	cout<<"display one by one:"<<endl;
	while(!s.empty()){
		cout<<"poping:\t"<<s.top()<<endl;
		s.pop();
	}

	Stack t,u;
	t=u=s;
	t.display(cout);
	u.display(cout);

	return 0;
}