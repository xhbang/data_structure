#include <iostream>
using namespace std;

#ifndef SEQ_QUEUE_H
#define SEQ_QUEUE_H
template <typename T>
class SeqQueue{
private:
	T *data;
	int front;
	int rear;
	int size;
public:
	SeqQueue(int defaultSize=100):size(defaultSize),front(0),rear(0){
		data =new T[defaultSize];
	}
	~SeqQueue(){
		delete [ ]data;			//never forget the "[ ]"
		front=rear=size=0;		//也许是多余的
	}
	int En_Queue(T item);		//返回1成功
	T De_Queue();			//会删去
	T Front_Queue();		//只读
	int Is_Empty();

};

template <typename T>
int SeqQueue<T>::En_Queue(T item){
	if(((rear+1)%size)!=front){
		data[rear]=item;
		rear=(rear+1)%size;
		return 1;
	}
	else
		return 0;
}

template <typename T>
T SeqQueue<T>::De_Queue(){
	if(front!=rear){
		T x=data[front];
		front=(front+1)%size;
		return x;
	}
	else 
		return 0;
}

template <typename T>
T SeqQueue<T>::Front_Queue(){
	if(front!=rear){
		T x=data[front];
		return x;
	}
	else return 0;
}

template <typename T>
int SeqQueue<T>::Is_Empty(){
	return rear==front;
}

//test
/*

int main(){
	SeqQueue<int> q;
	for(int i=0;i<5;i++)
		q.En_Queue(i);
	int num;
	while(!q.Is_Empty()){
		num=q.De_Queue();
		cout<<num<<"\t";
	}
	return 0;
}
*/
#endif
