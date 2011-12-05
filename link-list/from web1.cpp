#ifndef Node_H 
#define Node_H 

template <class Type> class Node 
{
 public:
	  Type data;
	  Node<Type> *link;
	  Node() : data(Type()), link(NULL) {} 
	  Node(const Type &item) : data(item), link(NULL) {}
	  Node(const Type &item, Node<Type> *p) : data(item), link(p) {}
 };
#endif


#ifndef List_H
#define List_H
#ifndef TURE
 #define TURE 1
#endif
#ifndef FALSE
 #define FALSE 0
#endif

typedef int BOOL;

#include "Node.h"

template <class Type> class List //?????
{
 //????????????????????,?current????
 //????“?1???”??0???,???,????1?,????????0???
 public:
  List() { first = current = last = new Node<Type>; prior = NULL; }
  ~List() { MakeEmpty(); delete first; }
   void MakeEmpty() //???
  { 
   Node<Type> *q;
   while (first->link != NULL)
   {
    q = first->link;
    first->link = q->link;
    delete q;
   }
   Initialize();
  }
  BOOL IsEmpty()
  {
   if (first->link == NULL) 
   {
    Initialize();
    return TURE;
   }
   else return FALSE;
  }
  int Length() const //????????????? 
  {
   Node<Type> *p = first->link;
   int count = 0;
   while (p != NULL)
   {
    p = p->link;
    count++;
   }
   return count;
  }
  Type *Get()//?????????????
  {
   if (current != NULL) return &current->data;
   else return NULL;
  }
  BOOL Put(Type const &value)//???????data,???value
  {
   if (current != NULL)
   {
    current->data = value;
    return TURE;
   }
   else return FALSE;
  }

  Type *GetNext()//???????????????????,???current
  {
   if (current->link != NULL) return &current->link->data;
   else return NULL;
  }
  Type *Next()//??current??????,??????????
  {
   if (current != NULL && current->link != NULL)
   {
    prior = current; 
    current = current->link;
    return &current->data;
   }
   else
   {
    return NULL;
   }
  }
  void Insert(const Type &value)//????????????,???current
  {
   Node<Type> *p = new Node<Type>(value, current->link);
   current->link = p;
  }
  BOOL InsertBefore(const Type &value)//?????????????,???current,??prior
  {
   Node<Type> *p = new Node<Type>(value);
   if (prior != NULL)
   {
    p->link = current;
    prior->link = p;
    prior = p;
    return TURE;
   }
   else return FALSE;
  } 

  BOOL Locate(int i)//??current??i???
  {
   if (i <= -1) return FALSE;
    current = first->link;
    for (int j = 0; current != NULL && j < i; j++, current = current->link) 
     prior = current;
     if (current != NULL) return TURE;
     else return FALSE;
  }

  void First()//??current???
  {
   current = first;
   prior = NULL;
  }
  void End()//??current???
  {
   if (last->link != NULL)
   {
    for ( ;current->link != NULL; current = current->link)
     prior = current;
     last = current;
   }
   current = last; 
  }

  BOOL Find(const Type &value)//??current?????value???
  {
   if (IsEmpty()) return FALSE;
   for (current = first->link, prior = first; current != NULL && current->data != value;
   current = current->link)
    prior = current;
    if (current != NULL) return TURE;
    else return FALSE;
  }
  BOOL Remove()//??????,current???????,??current???,???current = NULL
  {
   if (current != NULL && prior != NULL)
   {
    Node<Type> *p = current;
    prior->link = p->link;
    current = p->link;
    delete p;
    return TURE;
   }
   else return FALSE;
  }

  BOOL RemoveAfter()//????????????,???current
  {
   if (current->link != NULL && current != NULL)
   {
    Node<Type> *p = current->link;
    current->link = p->link;
    delete p;
    return TURE; 
   }
   else return FALSE;
  }

  friend ostream & operator << (ostream & strm, List<Type> &l)
  {
   l.First();
   while (l.current->link != NULL) strm << *l.Next() << " " ;
    strm << endl;
    l.First();
    return strm;
  }

  protected:

  /*???????????????????Insert(),Remove(),RemoveAfter()?????last?????last?????????public????????,????????last???????????,?????????,?????????????Insert(),Remove()???????????protected,?????????????*/ void LastInsert(const Type &value)

 {
  Node<Type> *p = new Node<Type>(value, last->link);
  last->link = p;
  last = p;
 }

 void Initialize()//???????????
 {
  current = last = first;
  prior = NULL;
 }

 //??????????Node<Type>??,???List?????
 
 Node<Type> *pGet()
 {
  return current;
 }
 Node<Type> *pNext()
 {
  prior = current;
  current = current->link;
  return current;
 }

 Node<Type> *pGetNext()
 {
  return current->link;
 }

 Node<Type> *pGetFirst()
 {
  return first;
 }

 Node<Type> *pGetLast()
 {
  return last;
 }

 Node<Type> *pGetPrior()
 {
  return prior;
 }

 void PutLast(Node<Type> *p)
 {
  last = p;
 }
//?????????????????,????????

 void Insert(Node<Type> *p)
 {
  p->link = current->link;
  current->link = p;
 }
 void InsertBefore(Node<Type> *p)
 {
  p->link = current;
  prior->link = p;
  prior = p;
 } 

 void LastInsert(Node<Type> *p)
 {
  p->link = NULL;
  last->link = p;
  last = p;
 }

 Node<Type> *pRemove()
 { 
  if (current != NULL && prior != NULL)
  {
   Node<Type> *p = current;
   prior->link = current->link;
   current = current->link;
   return p;
  }
  else return NULL;
 }

 Node<Type> *pRemoveAfter()
 {
  if (current->link != NULL && current != NULL)
  {
   Node<Type> *p = current->link;
   current->link = current->link->link;
   return p; 
  }
  else return NULL;
 }

 private:
  List(const List<Type> &l);
  Node<Type> *first, *current, *prior, *last;
  //??????last,????????End()???last??
};

#endif