/*
 * list.h
 *
 *  Created on: Jan 14, 2019
 *      Author: willi
 */

#ifndef LIST_H_
#define LIST_H_
#include "node.h"

using namespace std;

class List{
public:
	List();
	~List();
	bool empty() const;
	unsigned size() const;
	void add(int);
	void print();
	void clear();
	void removeValue(int);

private:
	int sz;
	Node* head;
	Node* tail;
	void initialize();
};
List::List(){
	sz = 0;
	head = new Node();
	tail = new Node();
	tail->setNext(head);
}

List::~List(){
	clear();
}

void List::add(int value){
	sz++;
	Node* end;
	Node* tempAdd;
	tempAdd = new Node(value);
	end = tail->getNext();
	end->setNext(tempAdd);
	tail->setNext(tempAdd);

}
void List::clear(){
	Node*temp;
	Node*trailTemp;
	temp = head;
	while(temp->getNext()!=NULL){
		trailTemp = temp->getNext();
		temp = temp->getNext();
		delete trailTemp;
		trailTemp = NULL;
		sz--;
	}
}
void List::removeValue(int value){
	Node* temp;
	Node* tempTwo;
	temp = head;
	while(temp->getNext()!=NULL){
		tempTwo = temp->getNext();
		if(tempTwo->getValue()==value){
			temp->setNext(tempTwo->getNext());
			tempTwo->setNext(NULL);
			delete tempTwo;
			sz--;
		}
		temp = temp->getNext();
	}
}
void List::print(){
	Node* temp;
	temp = head;
	int count = 0;
	while(temp->getNext()!=NULL){
		count++;
		if(count%25==1){
			cout<<endl;
		}
		temp=temp->getNext();
		cout<<temp->getValue()<<" ";
	}
	cout<<endl;
}

#endif /* LIST_H_ */
