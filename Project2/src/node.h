/*
 * node.h
 *
 *  Created on: Mar 17, 2019
 *      Author: willi
 */

#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <fstream>
#include <string>
#include <new>

class Node{
public:
	Node();
	Node(int);
	void setValue(int);
	int getValue();
	Node* getLC();
	Node* getRC();
	Node* getParent();
	void setLC(Node*);
	void setRC(Node*);
	void setParent(Node*);
	int childrenNumber();
	bool isLC();
	bool isRC();
	int getHeight();
	void increment();
	void setHeight(int);
	void updateHeight();
	void print();
private:
	Node *leftChild;
	Node *rightChild;
	Node *parent;
	int value;
	int height;

};


Node::Node(){
	value = 0;
	this->leftChild = NULL;
	this->rightChild = NULL;
	this->parent = NULL;
	height = 0;
}

Node::Node(int value){
	this->value = value;
	this->leftChild = NULL;
	this->rightChild = NULL;
	this->parent = NULL;
	height = 0;
}

int Node::childrenNumber(){
	if(rightChild==NULL&&leftChild==NULL){
		return 0;
	}
	else if(rightChild!=NULL&&leftChild!=NULL){
		return 2;
	}
	return 1;
}
void Node::setValue(int value){
	this->value = value;
}

int Node::getValue(){
	return value;
}

Node* Node::getRC(){
	return rightChild;
}
Node* Node::getLC(){
	return leftChild;
}
Node* Node::getParent(){
	return parent;
}

void Node::setLC(Node* child){
	leftChild = child;
}

void Node::setRC(Node* child){
	rightChild = child;
}

void Node::setParent(Node* parent){
	this->parent = parent;
}

bool Node::isLC(){
	Node* tempParent = this->getParent();
	return tempParent->getLC()==this;
}
bool Node::isRC(){
	Node* tempParent = this->getParent();
	return tempParent->getRC()==this;
}

void Node::increment(){
	height++;
}
int Node::getHeight(){
	return height;
	std::cout<<"in my getHeight"<<std::endl;
}
void Node::setHeight(int myHeight){
	height = myHeight;
}

void Node::updateHeight(){
	if(leftChild->getHeight()>rightChild->getHeight()){
		height+=leftChild->getHeight();
	}
	else{
		height+=rightChild->getHeight();
	}
}

void Node::print(){
//	std::cout<<value<<", "<<this<< ", P:"<<parent<<", LC: "<<leftChild<<", RC: "<<rightChild
//			<<std::endl;
	std::cout<<value;
}



#endif /* NODE_H_ */
