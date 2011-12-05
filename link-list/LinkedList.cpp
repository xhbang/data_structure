/*实验六
实验名称：泛型程序设计和STL编程
实验类型：验证型
实验目的：了解C++标准模板STL的容器类的
使用方法；应用标准C++模板库（STL）通用算
法和函数对象实现查找和排序。
实验原理：数组类、链表、栈类和队列类以
及查找、排序算法的使用技术；C++标准模板库（STL）的
使用方法，泛型程序设计的机制。 
实验内容：
（1）	使用C++标准模板库（STL）中的双向对
列类（deque）编写程序实现链表类（LinkedList）。
在测试程序中声明两个整型队列A和B，分别插入5个元素，
然后把B中的元素加入A的尾部；
（2）	声明一个整型数组，使用C++标准模板库（STL）
中的查找算法find()进行数据的查找，然后应用排序算法Sort()，
并配合使用标准函数对象Greater<T>对数据进行升序和降序排序。
*/
#include<iostream>
#include<deque>
#include<string>
using namespace std;

template<typename T>
class LinkedList{
private:
	deque<T> head;	
public:
	LinkedList()
	{	
	}
	LinkedList(deque<T> de)
	{
		head = de;
	}
/*
	~LinkedList(){
		destroy head;
	}

*/	
	void push_back(const T& ele)
	{
		head.push_back(ele);
	}
	void push_front(const T& ele)
	{
		head.push_front(ele);
	}

	void push_mid(const int loc,const T& ele)
	{
		deque<T>::iterator iter;
		int i;

		if(loc>head.size()+1 || loc<=0)
			throw 1;
		T tem=ele;
		T tem1;
		for(i=1,iter=head.begin();iter!=head.end();i++,iter++)
			if(i>=loc)
				if(i==loc)
				{
					tem=*iter;
					*iter=ele;
				}
				else
				{
					tem1=tem;
					tem=*iter;
					*iter=tem1;
					/*tem=tem+*iter;
					*iter=tem-*iter;
					tem=tem-*iter;*/
				}
				head.push_back(tem);
	}
	LinkedList<T> operator + (LinkedList<T>& L)
	{
		deque<T>::iterator iter;
		for(iter=L.head.begin();iter!=L.head.end();iter++)
		{
			
			head.push_back(*iter);

		}
		return *this;
	}
		
				
	friend ostream& operator <<(ostream& os,LinkedList<T>& L)
	{
		deque<T>::iterator iter;
		
		for(iter=L.head.begin();iter!=L.head.end();iter++)
		{
			os<<*iter;
			if(iter!=L.head.end()-1) 
				os<<"->";
		}
	
		return os;
	}


};
int main()
{	
	int loc;
	bool isOk=false;

	string ele;

	deque<string> A(5,"99");
	deque<string> B(5,"abc");

	LinkedList<string> list1(A);
	LinkedList<string> list2(B);
	cout<<list1<<endl;
	cout<<list2<<endl;
	cout<<"====================================="<<endl;
	list1.push_front("A");
	list2.push_front("B");
	cout<<list1<<endl;
	cout<<list2<<endl;

	cout<<"====================================="<<endl;	
	cout<<"请输入插入的元素值：";
	cin>>ele;
	while(!isOk){
		try{	
			cout<<"请输入插入位置：";
			cin>>loc;
			list2.push_mid(loc,ele);
			isOk=true;
		}catch(int x){
			cout<<"不是一个合适的位置！"<<endl;
			isOk=false;
		}
	}
	cout<<list2<<endl;
	cout<<"====================================="<<endl;

	list1+list2;
	cout<<"list1+list2 = "<<list1+list2<<endl;



	return 0;
	
}