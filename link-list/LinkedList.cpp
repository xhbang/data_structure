/*ʵ����
ʵ�����ƣ����ͳ�����ƺ�STL���
ʵ�����ͣ���֤��
ʵ��Ŀ�ģ��˽�C++��׼ģ��STL���������
ʹ�÷�����Ӧ�ñ�׼C++ģ��⣨STL��ͨ����
���ͺ�������ʵ�ֲ��Һ�����
ʵ��ԭ�������ࡢ����ջ��Ͷ�������
�����ҡ������㷨��ʹ�ü�����C++��׼ģ��⣨STL����
ʹ�÷��������ͳ�����ƵĻ��ơ� 
ʵ�����ݣ�
��1��	ʹ��C++��׼ģ��⣨STL���е�˫���
���ࣨdeque����д����ʵ�������ࣨLinkedList����
�ڲ��Գ����������������Ͷ���A��B���ֱ����5��Ԫ�أ�
Ȼ���B�е�Ԫ�ؼ���A��β����
��2��	����һ���������飬ʹ��C++��׼ģ��⣨STL��
�еĲ����㷨find()�������ݵĲ��ң�Ȼ��Ӧ�������㷨Sort()��
�����ʹ�ñ�׼��������Greater<T>�����ݽ�������ͽ�������
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
	cout<<"����������Ԫ��ֵ��";
	cin>>ele;
	while(!isOk){
		try{	
			cout<<"���������λ�ã�";
			cin>>loc;
			list2.push_mid(loc,ele);
			isOk=true;
		}catch(int x){
			cout<<"����һ�����ʵ�λ�ã�"<<endl;
			isOk=false;
		}
	}
	cout<<list2<<endl;
	cout<<"====================================="<<endl;

	list1+list2;
	cout<<"list1+list2 = "<<list1+list2<<endl;



	return 0;
	
}