#include <iostream>
//#include <iomapip>		//set

using namespace std;

#ifndef BST_TREE_H
#define BST_TREE_H

template <typename DataType>
class BST{

	BST();
	bool empty() const;		//�Ƿ�Ϊ��
	void inorder(ostream &out) const;
	bool search(const DataType &item) const;
//	void graph(ostream &out) const;

private:


//----------------------------------------�ڵ�����
	class BinNode{
	public:							
		DataType data;
		BinNode *left;
		BinNode *right;

		BinNode():left(0),right(0)	{};		//���ֹ��캯�����ֱ��Ӧ��������
		BinNode(DataType item=0):data(item),left(0),right(0)	{};		//ӛ�ô���̖
	};
//------------------------------------------
	typedef BinNode*  pBinNode;
	pBinNode myroot;

	void inorderAux(ostream &out,BST<DataType>::pBinNode subtree) const;		//inorder�ĸ�������
//	void graphAux(ostream &out,int indent,BST<DataType>::pBinNode subtree) const;
	bool  searchAux(const DataType &item,BST<DataType>::pBinNode) const;
	void insert(const DataType& item);
//ɾ������δд

};
template <typename DataType>
inline BST<DataType>::BST():myroot(0);
{}

template <typename DataType>
inline bool BST<DataType>::empty() const{
	return myroot==0;
}

template <typename DataType>												//ת�Ƹ�������,�������binTreeObj.inorder(argument list)
inline void BST<DataType>::inorder(ostream &out) const{
	inorderAux(out,myroot);
}

template <typename DataType>												//��ʼ����,inorderAux(parameter_list,pointer)
void BST<DataType>::inorderAux(ostream &out,BST<DataType>::pBinNode subtree) const{	
	if(subtree !=0){
		inorderAux(out,subtree->left);
		out<<subtree->data<<endl;
		inorderAux(out,subtree->right);
	}
}

/*ͼ�λ����������ʱ����
template <typename DataType>
inline void BST<DataType>::graph(ostream &out) const{
	graphAux(out,0,myroot);
}

template <typename  DataType>		//ͼ�λ����
void BST<DataType>::graphAux(ostream &out,int indent,BST<DataType>::pBinNode subtree) const{
	if(subtree!=0){
		graphAux(out,indent+8,subtree->right);
		out<<setw(indent)<<" "<<subtree->data<<endl;
		graphAux(out,indent+8,subtree->left);
	}
}
*/

//���ң��ǵݹ�͵ݹ�
template <typename DataType>
inline bool BST<DataType>::search(const DataType &item) const{
	searchAux(item,myroot);
} 

template <typename DataTaype>
boo BST<DataType>::searchAux(const DataType& item,BST<DataType>::pBinNode subtree){
	if(subtree==0)
		return false;
	else if(subtree->data >item)
		return searchAux(item,subtree->left);
	else if(subtree->data <item)
		return searchAux(item,subtree->right);
	else 
		return true;		//���Զ�����ȥ�ˣ��ҵ���
}

/*�ǵݹ鷽����
template <typename DataType>
bool BST<DataType>::search(const DataType & item) const{
	pBinNode current=myroot;
	bool found=0;
	while(!found && current!=0){
		if(item<current->data)
			current=current->left;
		else if(item > current->data)
			current=current->right;
		else
			found=true;
	}
	return found;
}
*/

template <typename DataType>
void BST<DataType>::search(const DataType &item){
	pBinNode current=myroot,parent=0;
	bool found=false;
	while(!found && current!=0){
		parent=current;
		if(item<current->data)
			current=current->left;
		else if(item> current->data)
			current=current->right;
		else 
			found=true;
	}
	if(found){
		current= new BST<DataType>::BinNode(item);
		if(parent==0)
			myroot=current;		//��Ӧ����current ΪNULL
		else if(item<parent->data)
			parent->left=current;
		else if(item>parent->data)
			parent->right=current;
	}
	else{
		cout<<"This item is already in the BST"<<endl;
	}
}


/*����ĵݹ�汾
template <DataType>
void BST<DataType>::insert(const DataType &item){
	insertAux(item,myroot);
}

void BST<DataType>::insertAux(const DataType &item,BST<DataType>::pBinNode & subtree){
	if(subtree==0)		//����
		subtree=new BST<DataType>::BinNode(item);
	else if(item<subtree->data)
		searchAux(item,subtree->left);
	else if(item>subtree->data)
		seatchAux(item,subtree->right);
	else
		cerr<<"Already find the item in the BST"<<endl;
}
*/

#endif
