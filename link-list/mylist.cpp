/*
�������汾��һ��������һ���ṹ���ΪNode,�������Ѿ����㽲��˼·,�����˵�
�ڶ���˼·���ǱȽϼ򵥣�ֱ������deque������һЩSTL����
*/
#include <iostream>
#include <deque>
#include <stdlib.h>		//exit,���������׳��쳣
//#include <string>		//���Ҫ��string��Ϊ�䴢������

using namespace  std;

template <typename T>
class mylist{
private:
	deque<T> myque;
//	int size;		//���ڿ����Ƿ���Ҫ,Ӧ�ò���Ҫ����Ϊ�Ƕ�myque�����޸ģ���size��ȷ����
public:
	//��Ҫ�ļ�������
	mylist() {}
	mylist(deque<T> s) {myque=s;}		//��������
	void push_front(const T&item);
	void push_end(const T&item);		//same:push_back()
	void insert(int loc,const T&item);
	inline int mylength(){return myque.size();}

	//void print();		//�ò��������ؽ��

	friend ostream& operator<<(ostream &out,mylist<T>& my){
		for(deque<T>::iterator iter=my.myque.begin();iter!=my.myque.end()-1;iter++){
				out<<*iter<<"--";
		}
		out<<*iter<<endl;
		return out;
	}

	mylist<T>& operator+(mylist<T>& my);		//����1��DEBUG;����2����ô����ͬ����

};

//definition:

/*
template <typename T>
void mylist<T>::insert(int loc,const T&item){
		deque<T>::iterator iter;
		int i;

		if(loc>myque.size()+1 || loc<=0){
			cout<<"ERROR in input"<<endl;
			exit(1);			//�������׳��쳣
		}
			
		T tem,tem1;		//������ʱ�������ݳ�־��ʾ
		for(i=1,iter=myque.begin();iter!=myque.end();i++,iter++){
			if(i>=loc)
				if(i==loc)
				{
					tem=*iter;		//��ֵ
					*iter=item;		//��ֵ
				}
				else
				{
					tem1=tem;		//
					tem=*iter;		//��ֵ
					*iter=tem1;		//��ֵ
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

//��ʱ�����⣬��δ���,�������ﲻ����const
template <typename T>
mylist<T>& mylist<T>::operator+(mylist<T>& my){
	for (deque<T>::iterator iter=my.myque.begin();iter!=my.myque.end();iter++){
		myque.push_back(*iter);
	}
	return *this;
}


//�����insert
template <typename T>
void mylist<T>::insert(int loc,const T&item){		//loc������loc�ϲ壬�����Ԫ��ȫ������λ��
	T temp;
	deque<T>::iterator iter1,iter;
	iter1=myque.begin();
	//�쳣��⣬�ԣ�����
	int i=1;
	while(i++<loc){
		iter1++;
	}
	temp=*(myque.end());
	myque.push_back(temp);
	for(iter=myque.end()-1;iter>iter1;iter--){		//�����end��ʼ��������Ҳ�����end����û�ռ䣿
		*iter=*(iter-1);
	}
	*iter=item;
}


//test
int main(){
	deque<int> A(4,999);
	deque<int> A2(7,23);
	deque<char> B(7,'6');
//����ʵ�ֲ��Ǵ�deque�ĸ��ƹ���

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

	cout<<(ilist+ilist2)<<endl;		//����:����������ͬ���͵����
	
	return 0;

}

