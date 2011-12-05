#include <iostream.h>
#include <string.h>

int zheban(string *s,int sz,string source);
int xianxing(string *s,string source);

int main(){
	string arr[10]={"auk","bat","cow","eel","elk","fox","gnu","pig","rat"};
	int loc1,loc2;
	string source;
	cout<<"input the string to find"<<endl;
	cin>>source;
	loc1=zheban(arr,10,string source);
	loc2=xianxing(arr,string source);
}

int zheban(string *s,int sz,string source){
	int middle,first,end,loc;
	bool found=false;
	first=0,end=sz-1,middle=(first+end)/2;
	while(first<=end && !found){
		if(strcmp(s[middle],source)>0)
			last=middle-1;
		else(strcmp(s[middle,source])<0)
			first=middle+1;
		else
			found=true;
	}
	return first;
}

int xianxing(string *s,string source){
	bool found=false;
	int i=0;
	if(*s && !found){
		if(strcmp(s,source)==0)
			found=true;
		else{
			s++;
			i++;
		}
	}
	return i;
}