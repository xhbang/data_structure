#include <new>
#include <cassert>
#include "stack.h"
using namespace std;			//very important


Stack::Stack(int numElement){
	assert(numElement>0);
	icapacity=numElement;

	myArray=new(nothrow)  ElemType[icapacity];
	if(myArray !=0)
		itop=-1;
	else{
		cerr<<"NOT ENOUGH ROOM\n";
		exit(1);
	}
}

Stack::Stack(const Stack& original):icapacity(original.icapacity),itop(original.itop){
	myArray=new(nothrow) ElemType[icapacity];
	if(myArray){
		for(int pos=0;pos<=itop;pos++){							//注意是小于等于
			myArray[pos]=original.myArray[itop];
		}
	}
	else{
		cerr<<"NOT ENOUGH RAM!\n"<<endl;
		exit(1);
	}
}

const Stack& Stack::operator=(const Stack & right){			//定义深度复制
	if (this!=&right){
		if(icapacity != right.icapacity){
			delete [ ] myArray;
			icapacity=right.icapacity;
			myArray = new ElemType[icapacity];

			if(!myArray){
				cerr<<"NOT ENOUGH ROOM!\n";
				exit(1);
			}
		}
		itop=right.itop;
		for(int pos=0;pos<=itop;pos++)
			myArray[pos]=right.myArray[pos];
	}
}


Stack::~Stack(){
	delete [ ]myArray;	
}

void Stack::pop(){
	if(!empty())
		--itop;
	else
		cout<<"******ERROR:NO DATA DISPLAY,STACK EMPTY******"<<endl;
}

bool Stack::empty() const{
	return (itop==-1);
}

void Stack::push(const ElemType &value){
	if(itop<icapacity){
		++itop;
		myArray[itop]=value;
	}
	else
		cout<<"******ERROR,OVERFLOW!******"<<endl;

}

void Stack::display(ostream &out) const{
/*为什么这里有ERROR:左值
	while(!empty()){
		out<<"DATA:"<<myArray[ptop--]<<endl;
	}
*/

	for(int i=itop;i>=0;i--)
	out<<myArray[i]<<endl;
	cout<<"*****DISPLAY END*****"<<endl;
}

ElemType Stack::top() const{
	if(!empty())
		return myArray[itop];
	else{
		cout<<"*****STACK EMPTY!,RETURNING GARBAGE******"<<endl; 
		ElemType garbage=0;			//需要初始化
		return garbage;
	}
}