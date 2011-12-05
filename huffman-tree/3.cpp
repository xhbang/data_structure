//��������

template<class T>
class  Huffman {
	friend BinaryTree<int> HuffmanTree(T [], int);
public:
	operator T () const {return weight;}
public:
	  BinaryTree<int> tree;
	  T weight;
};


template <class T>
BinaryTree<int> HuffmanTree(T a[], int n)
{
	//����Ȩ������a[1->n] �����������
	//����һ�����ڵ���������
	Huffman<T> *w = new Huffman<T> [n+1];
	BinaryTree<int> z, zero;
	for (int i = 1; i <= n; i++) 
	{
		z.MakeTree(i, zero, zero);
		w[i].weight = a[i];
		w[i].tree = z;
	}

	//��������һ����С��
	MinHeap<Huffman<T> > H(1);
	H.Initialize(w,n,n);

	//�����е������Ϻϲ�
	Huffman<T> x, y;
	for (int i = 1; i < n; i++) 
	{
		H.DeleteMin(x);
		H.DeleteMin(y);
		z.MakeTree(0, x.tree, y.tree);
		x.weight += y.weight; x.tree = z;
		H.Insert(x);
	}

	H.DeleteMin(x); //�õ���������
	H.Deactivate();
	delete [] w;
	return x.tree;
}


//����
template <class T>
class Node {
	friend LinkedStack<T>;
	friend LinkedQueue<T>;
private:
	T data;
	Node<T> *link;
};


template<class T>
class LinkedQueue 
{
public:
	LinkedQueue() {front = rear = 0;}
	~LinkedQueue();
	bool IsEmpty() const {return ((front) ? false : true);}
	bool IsFull() const;
	T First() const; // ���ص�һ��Ԫ��
	T Last() const;  // �������һ��Ԫ��
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);
private:
	Node<T> *front;  // ָ���һ���ڵ�
	Node<T> *rear;   // ָ�����һ���ڵ�
};

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	Node<T> *next;
	while (front) 
	{
		next = front->link; 
		delete front; 
		front = next;
	}
}

template<class T>
bool LinkedQueue<T>::IsFull() const
{
	// �ж϶����Ƿ�����
	Node<T> *p;
	try 
	{
		p = new Node<T>;
		delete p;
		return false;
	}
	catch (NoMem) 
	{
		return true;
	}
}

template<class T>
T LinkedQueue<T>::First() const
{
	if (IsEmpty()) 
		throw OutOfBounds();

	return front->data;
}

template<class T>
T LinkedQueue<T>::Last() const
{
	if (IsEmpty()) 
		throw OutOfBounds();

	return rear->data;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{
	Node<T> *p = new Node<T>;
	p->data = x;
	p->link = 0;

	// �ڶ���β������½ڵ�
	if (front) 
		rear->link = p;
	else 
		front = p;

	rear = p;

	return *this;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{
	if (IsEmpty()) 
		throw OutOfBounds();

	x = front->data;

	// ɾ����һ���ڵ�
	Node<T> *p = front;
	front = front->link;
	delete p;

	return *this;
}


//������
template <class T>
class BinaryTreeNode {
	friend BinaryTree<T>;
	friend BSTree<T,int>;
	friend DBSTree<T,int>;
public:
	BinaryTreeNode() {LeftChild = RightChild = 0;}
	BinaryTreeNode(const T& e){data = e; LeftChild = RightChild = 0;}
	BinaryTreeNode(const T& e, BinaryTreeNode *l,BinaryTreeNode *r) {data = e; LeftChild = l; RightChild = r;}
private:
	T data;
	BinaryTreeNode<T> *LeftChild,  // ������
					  *RightChild; // ������
};




template<class T>
class BinaryTree 
{
	friend BSTree<T,int>;
	friend DBSTree<T,int>;
public:
	BinaryTree() {root = 0;};
	~BinaryTree(){}; 
	bool IsEmpty() const {return ((root) ? false : true);}
	bool Root(T& x) const;
	void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void PreOrder(void(*Visit)(BinaryTreeNode<T> *u)) {PreOrder(Visit, root);}
	void InOrder(void(*Visit)(BinaryTreeNode<T> *u)) {InOrder(Visit, root);}
	void PostOrder(void(*Visit)(BinaryTreeNode<T> *u)) {PostOrder(Visit, root);}
	void LevelOrder(void(*Visit)(BinaryTreeNode<T> *u));
	void PreOutput() {PreOrder(Output, root); cout << endl;}
	void InOutput() {InOrder(Output, root); cout << endl;}
	void PostOutput() {PostOrder(Output, root); cout << endl;}
	void LevelOutput() {LevelOrder(Output); cout << endl;}

	void Delete() {PostOrder(Free, root); root = 0;}
	int Height() const {return Height(root);}
	int Size(){_count = 0; PreOrder(Add1, root); return _count;}
private:
	BinaryTreeNode<T> *root;
	void PreOrder(void(*Visit)(BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
	void InOrder(void(*Visit)(BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
	void PostOrder(void(*Visit)(BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
	static void Free(BinaryTreeNode<T> *t) {delete t;}
	static void Output(BinaryTreeNode<T> *t) {cout << t->data << ' ';}
	static void Add1(BinaryTreeNode<T> *t) {_count++;}
	int Height(BinaryTreeNode<T> *t) const;
};

template<class T>
bool BinaryTree<T>::Root(T& x) const
{
	if (root) 
	{ 
		x = root->data;
		return true;
	}
	else 
	{
		// û�и��ڵ�
		return false;  
	}
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	//��left, right �� element�ϲ���һ������,left,right��this�����ǲ�ͬ����
	root = new BinaryTreeNode<T>(element, left.root, right.root);

	// ��ֹ����left��right
	left.root = right.root = 0;
}

template<class T>
void BinaryTree<T>::BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	if (!root) 
		throw BadInput();

	//�ֽ���
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;

	delete root;
	root = 0;
}

template<class T>
void BinaryTree<T>::PreOrder( void(*Visit)(BinaryTreeNode<T> *u), BinaryTreeNode<T> *t)
{
	if(t) 
	{
		Visit(t);
		PreOrder(Visit, t->LeftChild);
		PreOrder(Visit, t->RightChild);
	}
}

template <class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T> *u), BinaryTreeNode<T> *t)
{
	if(t) 
	{
		InOrder(Visit, t->LeftChild);
		Visit(t);
		InOrder(Visit, t->RightChild);
	}
}

template <class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T> *u),BinaryTreeNode<T> *t)
{
	if(t) 
	{
		PostOrder(Visit, t->LeftChild);
		PostOrder(Visit, t->RightChild);
		Visit(t);
	}
}

template <class T>
void BinaryTree<T>::LevelOrder(void(*Visit)(BinaryTreeNode<T> *u))
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T> *t;
	t = root;
	while (t) 
	{
		Visit(t);

		if (t->LeftChild) 
			Q.Add(t->LeftChild);

		if (t->RightChild) 
			Q.Add(t->RightChild);

		try 
		{
			Q.Delete(t);
		}
		catch(OutOfBounds) 
		{
			return;
		}
	}
}

template <class T>
int BinaryTree<T>::Height(BinaryTreeNode<T> *t) const
{
	if(!t) 
		return 0;

	int hl = Height(t->LeftChild);
	int hr = Height(t->RightChild);
	if(hl > hr) 
		return ++hl;
	else 
		return ++hr;
}