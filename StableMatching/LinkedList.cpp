#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
	head = nullptr;
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

		to = head;
		from = from->forwardLink;

		while (from != nullptr) {
			to->forwardLink = new NodeType;
			to = to->forwardLink;
			to->component = from->component;


			from = from->forwardLink;
		}

		to->forwardLink = nullptr;
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

		to = head;
		from = from->forwardLink;

		while (from != nullptr) {
			to->forwardLink = new NodeType;
			
			to = to->forwardLink;
			to->component = from->component;
			from = from->forwardLink;
		}

		to->forwardLink = nullptr;
		
	}
	return *this;
}


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
	if(head!= nullptr)
	return head->component;

	return -1;
}
