#include <iostream>
#include "bst.h"
using namespace std;

int main(){
	//construct and empty()
	BST<int> iB;
	cout<<"consturct empty iB"<<endl;
	cout<<"BST"<<((ib.empty()==0)?"is":"is not"<<"empty");

	//inorder traverse
	cout<<"Now begin inorder traverse"<<endl;
	iB.inorder(cout);		//see the definition of inorder

	//insert
	int num=0;
	while(1){
		cout<<"plesae insert a num,(-999 to end)"<<endl;
		cin>>num;
		if(num==-999)
			break;
		iB.insert(num);
	}
	iB.inorder();
	//´úÌægraphicÊä³ö


	//search
	cout<<"input the number to want to find"<<endl;
	cout<<((iB.search(num))?"Found":"Not Found"<<endl;

	return 0;
}