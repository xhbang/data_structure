//LL: A linked list developed by Sonic. It contains a Node class and a LL class template.

/*Node class
   Basic operations:
     Constructor: Constructs an empty Node
	 Constructor(Overload): Construct a Node with data

   Private utility helper operations:
	 None

   Other operations described in the exercises:
	 None
   Note: The basic datatype of LL
*/

/*LL class
   Basic operations:
     Constructor:	Constructs an empty LL
	 Constructor:	Overload,to construct from an existing LL,using private copyList()
	 headCreate:	Create from the head
	 rearCreate:		Create from the rear
	 print:				Print all the element in the LL
	 insertFront:		Insert at the head
	 insertRear:		Insert at the rear
	 insertAt:			Insert before the current pointer
	 insertAfter:		Insert after the current pointer



	 operator=:		Overload,using private copyList()
	 operator<<:	Overload,redirect to "out"

   Private utility helper operations:
	 copyList:		An overload edition:from a LL


   Other operations described in the exercises:
	 headCreate:	create a LL from the head,without a head node,for fun
	 reatCreate:		create a LL from the rear,withou a head node,for fun
		
   Note: Execution terminates if memory isn't available for a new LL node.
*/



#include <iostream>
using namespace std;

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/***** Node class *****/
template <typename T>
class Node{
public:
	T data;
	Node * next;
/***** Function Members *****/
	Node()	{next=NULL;}
	Node(T in)	{data=in,next=NULL;}
};// end of class template declaration

/***** Linked List class *****/
template <typename T>
class LL{
private:
	Node<T> *head,*rear;
	Node<T> *pre,*current;
	int size;
public:
	//����
	LL(){
		size=0;
		head=rear=pre=current=NULL;
	}
	//����
	LL(){
		deleteall();
		deletepointer();
	}

	//��ʼ��,һ�㲻��
	void init(){
		deleteall();
		head=rear=pre=NULL;
		size=0;
	}
//�����ǽ���ϵ��
	//��ͷ�����ڵ�,û��ͷ�������

	//��β�������ڵ�,û��ͷ���

	//��ͷ�����ڵ�,��ͷ�������

	//��β�������ڵ�,��ͷ���

	//���ҽڵ㣨����ָ�룩
	//���ҽڵ㣨����λ�ã�
	//ȡ�ڵ�Ԫ��
	//��ĳһλ�ò���
	//ɾ��ĳһλ��Ԫ��
	

};// end of class template declaration


#endif