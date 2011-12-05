
class BinNode{
public:
	DataType data;
	BinNode *left;
	BinNode *right;

	BinNode():left(0),right(0){
	}

	BinNode(DataType item):data(item),left(0),right(0){
	}

};