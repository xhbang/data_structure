#include "tree.h"


int main(){
//	int data[80] = {1,2,-1,-1,3,-1,-1};
//  tree<int> treee;

	char data[80] = {'a','b','#','#','c','#','#'};
	tree<char> treee('#');

    treee.create(data, 7);
	cout<<"The height is:"<<treee.heigth()<<endl;
	cout<<"The size is :"<<treee.size()<<endl;
	treee.traverse();
	cout<<endl;

    cout<<"Finish testing... ..."<<endl;
	return 1;
}
