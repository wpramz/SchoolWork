/*
 * node.h
 *
 *  Created on: Apr 18, 2019
 *      Author: willi
 */

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <fstream>
#include <string>
#include <new>

using std::string;

class Node{
public:
	Node();
	Node(string);
	Node(string, Node*);
	void setValue(string);
	string getValue();
	void setNext(Node*);
	Node* getNext();
private:
	Node* next;
	string value;
};

Node::Node(){
	next = NULL;
	value = "";
}
Node::Node(string obj){
	next = NULL;
	value = obj;
}
Node::Node(string obj, Node* next){
	value = obj;
	setNext(next);
}
void Node::setValue(string obj){
	value = obj;
}
string Node::getValue(){
	return value;
}

void Node::setNext(Node* next){
	this->next= next;
}
Node* Node::getNext(){
	return next;
}



#endif /* NODE_H_ */
