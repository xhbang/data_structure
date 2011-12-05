/*
有两个版本，一个是利用一个结构体成为Node,我上午已经给你讲了思路,复杂了点
第二个思路就是比较简单，直接利用deque，用了一些STL操作
*/
#include <iostream>
#include <deque>
#include <stdlib.h>		//exit,本来可以抛出异常
//#include <string>		//如果要用string作为其储存类型

using namespace  std;

template <typename T>
class mylist{
private:
	deque<T> myque;
//	int size;		//正在考虑是否需要,应该不需要，因为是对myque做了修改，其size是确定的
public:
	//主要的几个操作
	mylist() {}
	mylist(deque<T> s) {myque=s;}		//拷贝复制
	void push_front(const T&item);
	void push_end(const T&item);		//same:push_back()
	void insert(int loc,const T&item);
	inline int mylength(){return myque.size();}

	//void print();		//用操作符重载解决

	friend ostream& operator<<(ostream &out,mylist<T>& my){
		for(deque<T>::iterator iter=my.myque.begin();iter!=my.myque.end()-1;iter++){
				out<<*iter<<"--";
		}
		out<<*iter<<endl;
		return out;
	}

	mylist<T>& operator+(mylist<T>& my);		//问题1：DEBUG;问题2：怎么处理不同类型

};

//definition:

/*
template <typename T>
void mylist<T>::insert(int loc,const T&item){
		deque<T>::iterator iter;
		int i;

		if(loc>myque.size()+1 || loc<=0){
			cout<<"ERROR in input"<<endl;
			exit(1);			//本来该抛出异常
		}
			
		T tem,tem1;		//用做临时变量，据陈志提示
		for(i=1,iter=myque.begin();iter!=myque.end();i++,iter++){
			if(i>=loc)
				if(i==loc)
				{
					tem=*iter;		//提值
					*iter=item;		//赋值
				}
				else
				{
					tem1=tem;		//
					tem=*iter;		//提值
					*iter=tem1;		//赋值
				}
		}
		myque.push_back(item);
}
*/

template <typename T>
void mylist<T>::push_front(const T&item){
	myque.push_front(item);
}

template <typename T>
void mylist<T>::push_end(const T&item){
	myque.push_back(item);
}

//暂时有问题，还未解决,就是这里不能用const
template <typename T>
mylist<T>& mylist<T>::operator+(mylist<T>& my){
	for (deque<T>::iterator iter=my.myque.begin();iter!=my.myque.end();iter++){
		myque.push_back(*iter);
	}
	return *this;
}


//倒序版insert
template <typename T>
void mylist<T>::insert(int loc,const T&item){		//loc就是在loc上插，后面的元素全部调换位置
	T temp;
	deque<T>::iterator iter1,iter;
	iter1=myque.begin();
	//异常检测，略，见上
	int i=1;
	while(i++<loc){
		iter1++;
	}
	temp=*(myque.end());
	myque.push_back(temp);
	for(iter=myque.end()-1;iter>iter1;iter--){		//如果从end开始倒序会出错，也许好似end那里没空间？
		*iter=*(iter-1);
	}
	*iter=item;
}


//test
int main(){
	deque<int> A(4,999);
	deque<int> A2(7,23);
	deque<char> B(7,'6');
//正在实现不是从deque的复制构造

	mylist<int> ilist(A);
	mylist<char> clist(B);
	mylist<int> ilist2(A2);

	ilist.push_front(123);
	ilist.push_end(987);

	cout<<ilist<<endl;
	cout<<clist<<endl;

	clist.push_front('b');
	clist.push_end('e');

	cout<<clist<<endl;
	cout<<"THE length is.."<<clist.mylength()<<endl;

	clist.insert(4,'O');
	cout<<clist<<endl;

	cout<<(ilist+ilist2)<<endl;		//问题:不能两个非同类型的相加
	
	return 0;

}

