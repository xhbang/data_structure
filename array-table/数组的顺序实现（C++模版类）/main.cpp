
/*----------------   基本测试文件   -------   Author:Hector -------*/

#include<iostream>
#include "Array.h"
using namespace std;
int main()
{
	int i,j,k,dim=3,bound1=3,bound2=4,bound3=5;
	char temp=0;
	Array<char> my(dim,bound1,bound2,bound3);
	for(i=0;i<bound1;i++)
		for(j=0;j<bound2;j++)
			for(k=0;k<bound3;k++)
				my.Assign('c',i,j,k);
	for(i=0;i<bound1;i++)
		for(j=0;j<bound2;j++)
			for(k=0;k<bound3;k++){
				my.Value(&temp,i,j,k);
				cout<<temp<<endl;
			}
			return 0;
}
