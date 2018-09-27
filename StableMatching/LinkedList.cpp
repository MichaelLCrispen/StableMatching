#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
	head = nullptr;
	//tail = nullptr;
	length = 0;
}


LinkedList::~LinkedList() {
	NodePtr temp;
	NodePtr curr = head;
	while (curr != nullptr) {
		temp = curr;
		curr = curr->forwardLink;
		delete temp;
	}
	head = nullptr;
	//tail = nullptr;
	return;
}

LinkedList::LinkedList(const LinkedList & otherLinkedList) {
	NodePtr from;
	NodePtr to;
	length = otherLinkedList.length;

	if (otherLinkedList.head == nullptr) {
		head = nullptr;
	}

	else {
		from = otherLinkedList.head;
		head = new NodeType;
		head->component = from->component;
		//head->reverseLink = nullptr;

		to = head;
		from = from->forwardLink;

		while (from != nullptr) {
			to->forwardLink = new NodeType;
			//to->forwardLink->reverseLink = to;
			to = to->forwardLink;
			to->component = from->component;


			from = from->forwardLink;
		}

		to->forwardLink = nullptr;
		//tail = to;
	}
}

const LinkedList & LinkedList::operator=(const LinkedList & otherLinkedList)
{
	NodePtr from;
	NodePtr to;
	length = otherLinkedList.length;

	if (otherLinkedList.head == nullptr) {
		head = nullptr;
	}

	else {
		from = otherLinkedList.head;
		head = new NodeType;
		head->component = from->component;
		//head->reverseLink = nullptr;

		to = head;
		from = from->forwardLink;

		while (from != nullptr) {
			to->forwardLink = new NodeType;
			//to->forwardLink->reverseLink = to;
			to = to->forwardLink;
			to->component = from->component;

			from = from->forwardLink;
		}

		to->forwardLink = nullptr;
		//tail = to;
	}
	return *this;
}

/*
void LinkedList::Insert(int data) {
	NodePtr newNode = new NodeType;
	newNode->component = data;

	//if(head)
		//head->reverseLink = newNode;

	newNode->forwardLink = head;
	head = newNode;

	if (head->forwardLink == nullptr)
		//tail = newNode;

	length++;
	return;
}
*/
void LinkedList::Push(int data) {

	NodePtr tmp = new NodeType;
	tmp->component = data;

	if (head == nullptr)
	{
		tmp->forwardLink = nullptr;
		head = tmp;
		length++;
	}
	else
	{
		tmp->forwardLink = head;
		head = tmp;
		length++;
	}
}

void LinkedList::Pop() {
	NodePtr tmp;

	if (head != nullptr)
	{
		tmp = head;
		head = head->forwardLink;
		length--;
		delete tmp;
	}
}


/*
void LinkedList::Delete(int data) {
	NodePtr prevPtr = nullptr;
	NodePtr currPtr = head;

	while (currPtr != nullptr && currPtr->component != data && currPtr->component < data) {
		prevPtr = currPtr;
	}

	if (currPtr != nullptr && currPtr->component == data) {

		currPtr = head;
		prevPtr = nullptr;
		while (currPtr->component != data) {
			prevPtr = currPtr;
			currPtr = currPtr->forwardLink;
		}


		if (currPtr == head) {
			head = currPtr->forwardLink;
			//head->reverseLink = nullptr;
		}

		else {
			prevPtr->forwardLink = currPtr->forwardLink;
			//prevPtr->reverseLink = currPtr->reverseLink;
		}

		//if (currPtr == tail)
			//tail = tail->reverseLink;


		delete currPtr;
		length--;
	}
}
*/

void LinkedList::Destroy() {
	NodePtr temp;
	NodePtr curr = head;
	while (curr != nullptr) {
		temp = curr;
		curr = curr->forwardLink;
		delete temp;
	}
	head = nullptr;
	//tail = nullptr;
	length = 0;

	return;
}


bool LinkedList::Search(int data) {
	NodePtr current = head;
	while (current != nullptr) {
		current = current->forwardLink;
		if (data == current->component)
			return true;
	}

	return false;
}

bool LinkedList::isEmpty() const {
	if (length == 0)
		return true;
	return false;
}

int LinkedList::Length() const {
	return length;
}

void LinkedList::PrintList() {
	NodePtr head = this->head;

	if (length == 0)
		std::cout << "This list is empty";

	while (head) {
		std::cout << head->component << " ";
		head = head->forwardLink;
	}
	return;
}

int LinkedList::Front() {
	return head->component;
}



//*******************TESTING FUNCTIONS****************

bool LinkedList::HeadNull() {
	if (head == nullptr) {
		return true;
	}

	return false;

}


bool LinkedList::TailNull() {
	//if (tail == nullptr) {
	//	return true;
	//}

	return false;
}


/*
int LinkedList::ReturnTailData() {
	return tail->component;
}
*/


