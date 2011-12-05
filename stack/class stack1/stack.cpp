#include <iostream>
#include "stack.h"
using namespace std;			//very important

Stack::Stack():ptop(-1){};		//ע����������

void Stack::pop(){
	if(!empty())
		--ptop;
	else
		cout<<"******ERROR:NO DATA DISPLAY,STACK EMPTY******"<<endl;
}

bool Stack::empty() const{
	return (ptop==-1);
}

void Stack::push(const ElemType &value){
	if(ptop<STACK_SIZE-1){
		++ptop;
		myArray[ptop]=value;
	}
	else
		cout<<"******ERROR,OVERFLOW!******"<<endl;

}

void Stack::display(ostream &out) const{
/*Ϊʲô������ERROR:��ֵ
	while(!empty()){
		out<<"DATA:"<<myArray[ptop--]<<endl;
	}
*/

	for(int i=ptop;i>=0;i--)
	out<<myArray[i]<<endl;
	cout<<"*****DISPLAY END*****"<<endl;
}

ElemType Stack::top() const{
	if(!empty())
		return myArray[ptop];
	else{
		cout<<"*****STACK EMPTY!,RETURNING GARBAGE******"<<endl; 
		ElemType garbage=0;			//��Ҫ��ʼ����
		return garbage;
	}
}