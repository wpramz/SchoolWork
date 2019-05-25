/*
 * binarySearchTree.h
 *
 *  Created on: Mar 18, 2019
 *      Author: willi
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_


#include "node.h"

class BinarySearchTree {
public:
	BinarySearchTree();
	void print();
	void print(Node*);
	void insert(int);
	void insert(Node*, Node*);
	void remove(int);
	Node* remove(Node*, int);
	Node* removeMin(Node*, Node*);
	Node* search(int);
	Node* getRoot();
	int getCount();

protected:
	Node* root;
	int count;
};

BinarySearchTree::BinarySearchTree() {
	root = NULL;
	count = 0;
}

Node* BinarySearchTree::getRoot() {
	return root;
}

void BinarySearchTree::insert(Node* temp, Node* newNode) {
	int newValue = newNode->getValue();
	if (newValue < temp->getValue()) {
		count++;
		if (temp->getLC() == NULL) {
			temp->setLC(newNode);
			newNode->setParent(temp);
		} else {
			insert(temp->getLC(), newNode);
		}
	} else if (newValue > temp->getValue()) {
		count++;
		if (temp->getRC() == NULL) {
			temp->setRC(newNode);
			newNode->setParent(temp);
		} else {
			insert(temp->getRC(), newNode);
		}
	}
}

void BinarySearchTree::insert(int value) {
	if (root == NULL) {
		root = new Node(value);
	} else {
		this->insert(root, new Node(value));
	}
}

void BinarySearchTree::remove(int target) {
	remove(root, target);
}
Node* BinarySearchTree::remove(Node* temp, int target) {
	if (temp != NULL) {
		if (target < temp->getValue()) {
			count++;
			remove(temp->getLC(), target);
		} else if (target > temp->getValue()) {
			count++;
			remove(temp->getRC(), target);
		} else if (temp->getLC() != NULL && temp->getRC() != NULL) {
			count++;
			Node* minRightST = removeMin(temp, temp->getRC());
			int tempValue = temp->getValue();
			temp->setValue(minRightST->getValue());
			minRightST->setValue(tempValue);
			remove(minRightST, tempValue);
		} else if (temp->getLC() == NULL && temp->getRC() == NULL) {
			count++;
			if (temp->isLC()) {
				temp->getParent()->setLC(NULL);
			} else {
				temp->getParent()->setRC(NULL);
			}
			delete temp;
		} else {
			Node* trash = temp;
			if (temp == root) {
				if (temp->getLC() != NULL) {
					root = temp->getLC();
				} else if (temp->getRC() != NULL) {
					root = temp->getRC();
				}
			} else if (temp->isLC()) {
				count++;
				if (temp->getLC() != NULL) {
					temp->getParent()->setLC(temp->getLC());
					temp->getLC()->setParent(temp->getParent());
				} else if (temp->getRC() != NULL) {
					temp->getParent()->setLC(temp->getRC());
					temp->getRC()->setParent(temp->getParent());
				}
			} else if (temp->isRC()) {
				count++;
				if (temp->getLC() != NULL) {
					temp->getParent()->setRC(temp->getLC());
					temp->getLC()->setParent(temp->getParent());
				} else if (temp->getRC() != NULL) {
					temp->getParent()->setRC(temp->getRC());
					temp->getRC()->setParent(temp->getParent());
				}
			}
			delete trash;
		}
	}
	return NULL;
}

Node* BinarySearchTree::removeMin(Node* parent, Node* child) {
	if (child != NULL) {
		if (child->getLC() != NULL) {
			return removeMin(child, child->getLC());
		} else {
			return child;
		}
	}
	return NULL;
}

Node* BinarySearchTree::search(int target) {
	Node* temp = root;
	while (temp != NULL) {
		if (target < temp->getValue()) {
			count++;
			temp = temp->getLC();
		} else if (target > temp->getValue()) {
			count++;
			temp = temp->getRC();
		} else if (target == temp->getValue()) {
			count++;
			return temp;
		}
	}
	return NULL;
}

void BinarySearchTree::print() {
	print(root);
	std::cout<<std::endl;
	std::cout <<"Number of Comparisons: "<<count<<std::endl;
}

void BinarySearchTree::print(Node* temp) {
	if (temp) {
		std::cout << " [";
		temp->print();
		if (temp->getLC() != NULL) {
			print(temp->getLC());
			if (temp->getRC() == NULL) {
				std::cout << " []";
			}
		}
		if (temp->getRC() != NULL) {
			if (temp->getLC() == NULL) {
				std::cout << " []";
			}
			print(temp->getRC());
		}
		std::cout << " ]";
	}
}

int BinarySearchTree::getCount(){
	return count;
}

#endif /* BINARYSEARCHTREE_H_ */
