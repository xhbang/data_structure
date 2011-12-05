#ifndef ZHANCLASS
#define ZHANCLASS
#include <iostream>
#include<vector>
#include<cstdlib>
using namespace std;

template <class T>
class Sqstack{
private:
	vector<T> sq;
public:
	Sqstack(){};
	~Sqstack(){};
	void clearStack(){sq.clear();}
	bool stackEmpty(){return sq.empty ();}
	T GetTop(){
		if(sq.empty()){
			cerr<<"empty!"<<endl;
			exit(1);
		}
		else
		return sq.back();
	}
	void Push(T x){sq.push_back(x);}
	
	T Pop(){
		if(sq.empty()){
			cerr<<"empty!"<<endl;
			exit(1);
		}
		else{
			T t=GetTop();
			sq.pop_back();
			return t;
		}
	}
};
#endif