#ifndef LinkedList_H
#define LinkedList_H


class LinkedList {

private:
	typedef int ItemType;
	struct NodeType;
	typedef NodeType* NodePtr;

public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList& otherlinkedlist);
	const LinkedList& operator=(const LinkedList& otherLinkedList);


	void Push(int data); 
	void Pop();  


	//void Insert(int data);
	//void Delete(int data);
	void Destroy();
	bool Search(int data);
	bool isEmpty() const;
	int  Length() const;
	void PrintList();

	//For Testing Purposes
	bool HeadNull();
	bool TailNull();
	int Front();
	//int ReturnTailData();


private:

	struct NodeType
	{
		ItemType component;
		NodePtr forwardLink;
		//NodePtr reverseLink;
	};

	NodePtr head;
	//NodePtr tail;


	int length;
};


#endif
