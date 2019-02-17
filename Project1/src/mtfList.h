/*
 * mtfList.h
 *
 *  Created on: Feb 12, 2019
 *      Author: willi
 */

#ifndef MTFLIST_H_
#define MTFLIST_H_
using namespace std;

#include "node.h"


class mtfList{
public:
	mtfList(int, int values[]);
	~mtfList();
	bool empty() const;
	unsigned size() const;
	void add(int);
	void print();
	void clear();
	void removeValue(int);
	void search(int);

private:
	int sz;
	Node *head;
	Node *tail;
};
mtfList::mtfList(int size, int values[]){
	sz = 0;
	head = new Node();
	tail = new Node();
	tail->setNext(head);
	for(int i = 0; i<size; i++){
		add(values[i]);
		//cout<<values[i]<<endl;
	}
}
bool mtfList::empty()const{
	if(sz==0){
		return true;
	}
	return false;
}
void mtfList::add(int value){
	sz++;
	Node* end;
	Node* tempAdd;
	tempAdd = new Node(value);
	end = tail->getNext();
	end->setNext(tempAdd);
	tail->setNext(tempAdd);
}

void mtfList::search(int target){
	if(!empty()){
		Node* temp;
		Node* tempTwo;
		temp = head;
		while(temp->getNext()!=NULL){
			tempTwo=temp->getNext();
			if(tempTwo->getValue() == target){
				temp->setNext(tempTwo->getNext());
				tempTwo->setNext(head->getNext());
				head->setNext(tempTwo);
			}
			temp = temp->getNext();
		}
	}
}
mtfList::~mtfList(){
	clear();
}
void mtfList::clear(){
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
void mtfList::print(){
	Node* temp;
	temp = head;
	int count = 0;
	while(temp->getNext()!=NULL){
		if(count%10==0){
			cout<<endl;
		}
		temp=temp->getNext();
		cout<<temp->getValue()<<" ";
		count++;
	}
	cout<<endl;
}
void mtfList::removeValue(int value){
	Node* temp;
	Node* tempTwo;
	temp = head;
	if(!empty()){
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
}


#endif /* MTFLIST_H_ */