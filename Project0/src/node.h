#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <new>

using namespace std;

class Node{
public:
	Node();
	Node(int);
	void setValue(int);
	int getValue();
	void setNext(Node*);
	Node* getNext();

private:
	int value;
	Node *nextNode;
};
Node::Node(){
	value = 0;
	this->nextNode = NULL;
}
Node::Node(int value){
	this->value = value;
	this->nextNode = NULL;
}
void Node::setValue(int value){
	this->value = value;
}
int Node::getValue(){
	return value;
}
void Node::setNext(Node* next){
	this->nextNode = next;
}
Node* Node::getNext(){
	return nextNode;
}


#endif
