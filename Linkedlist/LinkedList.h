#ifndef LINKLIST_CLASS
#define LINKLIST_CLASS

#include"Node.h"
#include<iostream>
using namespace std;

template<class T>
class LinkedList{
private:
	Node<T>* front,*rear;
	Node<T>* prePtr,*currPtr;	//记录表当前表遍历位置的指针，用于插入删除操作
	int size;
	//int position;

	Node<T>* GetNode(const T& data,Node<T>* next=0);
//	void FreeNode(Node<T>* p);//这个函数忘记使用了，囧 
	void CopyList(const LinkedList<T>& L);				//重载"=",函数使用

public:	
	LinkedList();
	LinkedList(const LinkedList<T>& L);
	~LinkedList();
	LinkedList<T>& operator = (const LinkedList<T>& L);

	friend ostream& operator <<(ostream& os,LinkedList<T>& L){			//<<重载很好,为什么不能放在外面
		Node<T>* p;
		for(p=L.front->NextNode();p;p=p->NextNode()){
			os<<p->GetData();
			if(p->NextNode()!=0) os<<',';
		}
		return os;
	}
	int ListSize();
	bool ListEmpty();

	void Reset(int loc=0);
	void Next();//
	bool EndOfList();//
//	int CurrentPosition();//

	void InsertFront(const T& data);
	void InsertRear(const T& data);
	void InsertAt(const T& data);
	void InsertAfter(const T& data);

	void DeleteFront();
	void DeleteAt();
	
	void SetData(T& data);

	void ClearList();

	void Print();
	
	/*提供一些插入查找函数//均由上述函数组合而成，因而存在的必要性不大*/
	int Find(T& data,int loc=0);
	void DeleteData(T& data,int loc=0);
	void InsertLoc(T& data,int loc);
};


template <class T>
LinkedList<T>::LinkedList(){
	size=0;
	front=new Node<T>;
//if(front->NextNode()==0) cout<<"right in gouzao"<<endl;
	prePtr=front;
	currPtr=prePtr->NextNode();
	rear=front;
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &L){
	front=new Node<T>;
//if(front->NextNode==0) cout<<"right in kaobeigouzao"<<endl;
//	front->next=0;
	rear=front;
	this->CopyList(L);	
	prePtr=front;	
	currPtr=prePtr->NextNode();
}
template <class T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T> &L){
	CopyList(L);
}

template <class T>
void LinkedList<T>::CopyList(const LinkedList<T> &L){
	ClearList();
	Node<T>* p;
	for(p=(L.front)->NextNode();p;p=p->NextNode())
		InsertRear(p->GetData());
	size=L.size;
	prePtr=front;	
	currPtr=prePtr->NextNode();
}

template <class T>
LinkedList<T>::~LinkedList(){
	ClearList();
	DeleteFront();
}
template <class T>
void LinkedList<T>::DeleteFront(){
	delete front;
	currPtr=prePtr=rear=front=0;
}
template <class T>
void LinkedList<T>::ClearList(){
	prePtr=front;
	currPtr=prePtr->NextNode();
	for(;prePtr!=rear;){
		DeleteAt();//Print();
//if(currPtr==rear) cout<<"last"<<endl;
	}
	size=0;
	rear=front;
	currPtr=prePtr->NextNode();
}
template <class T>
void LinkedList<T>::DeleteAt(){
	Node<T>* p=prePtr->DeleteAfter();
	if(p==0) 
		delete rear;
	else 
		delete p;
	currPtr=prePtr->NextNode();
	if(prePtr->NextNode()==0) rear=prePtr/*,cout<<"henhao"<<endl*/;
	size--;
}
template <class T>
Node<T>*	LinkedList<T>::GetNode(const T &data, Node<T> *next = 0){	//私有函数,建立节点
	Node<T>* p;
	p=new Node<T>(data);
//if(p->NextNode()==0) cout<<"right in getnode"<<endl;
	return p;
}

/*template <class T>//这个函数事实上我没使用=.= 
void LinkedList<T>::FreeNode(Node<T> *p){
	delete p;
}*/
template <class T>
int LinkedList<T>::ListSize(){
	return size;
}
template <class T>
bool LinkedList<T>::ListEmpty(){
	if(size==0)
		return true;
	else
		return false;
}
template <class T>
bool LinkedList<T>::EndOfList(){
	if(!currPtr->NextNode())
		return true;
	else
		return false;
}

template <class T>
void LinkedList<T>::InsertFront(const T &data){
	currPtr=GetNode(data,front->NextNode());
	front->InsertAfter(currPtr);
	size++;
	if(currPtr->NextNode()==0)
		rear=currPtr;/*,cout<<"rear move in insertfront"<<endl*/;
//	if(rear->NextNode()==0) cout<<"rear.next 正确"<<rear->GetData()<<endl;
}
template <class T>
void LinkedList<T>::InsertRear(const T &data){
	currPtr=GetNode(data);
	rear->InsertAfter(currPtr);
	rear=rear->NextNode();
	size++;
}
template <class T>
void LinkedList<T>::InsertAt(const T &data){
	currPtr=GetNode(data,currPtr);
	prePtr->InsertAfter(currPtr);
	size++;
}
template <class T>
void LinkedList<T>::InsertAfter(const T &data){
	prePtr=currPtr;
	currPtr=GetNode(data,currPtr->NextNode());
	if(prePtr==rear)
		rear=currPtr/*,cout<<"rear move in insertafter"<<endl*/;
	prePtr->InsertAfter(currPtr);
	size++;
}



template <class T>
void LinkedList<T>::Reset(int loc=0){
	prePtr=front;
	currPtr=prePtr->NextNode();
	for(int i=1;i<loc;i++){
		if(i>=size){
			cout<<"error.the currPtr will zhixiang the rear."<<endl;
			cout<<"the currPtr guoran zhixiang the rear."<<rear->GetData()<<"   and  "<<currPtr->GetData()<<endl;
			break;
		}
	//	cout<<"xian zai de curr"<<currPtr->GetData()<<endl;
		Next();
	//	cout<<"next hou de  curr"<<currPtr->GetData()<<endl;

	}
}

template <class T>
void LinkedList<T>::SetData(T& data){
	currPtr->SetData(data);
}
template <class T>
void LinkedList<T>::Next(){
	prePtr=currPtr;
	currPtr=currPtr->NextNode();
}



template <class T>
void LinkedList<T>::Print(){
	Node<T>* p;
//	cout<<rear->GetData()<<endl;
//	if(rear->NextNode()!=0)cout<<"wokao";
	for(p=front->NextNode();p;p=p->NextNode())
		cout<<p->GetData()<<",";
	cout<<endl;
	
}
template <class T>
int LinkedList<T>::Find(T& data,int loc=0){
	Reset(loc);
	for(int i=1;i<=size;Next(),i++)
		if(currPtr->GetData()==data)
			return i;
	return -1;
}
template <class T>
void LinkedList<T>::DeleteData(T& data,int loc=0){
	int i=Find(data,loc);
	if(i==-1)
		cout<<"NO the data."<<endl;
	else
		this->DeleteAt();
	size--;
}

template <class T>
void LinkedList<T>::InsertLoc(T& data,int loc){
	Reset(loc);
	if(currPtr==rear)
		this->InsertAfter(data);
	else
		this->InsertAt(data);
}



#endif
