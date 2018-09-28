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

	bool Search(int data);
	bool isEmpty() const;
	int  Length() const;
	void PrintList();
	int Front();


private:

	struct NodeType
	{
		ItemType component;
		NodePtr forwardLink;
		
	};

	NodePtr head;
	int length;
};


#endif
