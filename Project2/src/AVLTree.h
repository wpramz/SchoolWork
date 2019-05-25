/*
 * AVLTree.h
 *
 *  Created on: Mar 18, 2019
 *      Author: willi
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_
#include <cmath>
using namespace std;

#include "binarySearchTree.h"

class AVLTree: public BinarySearchTree {
public:
	AVLTree();
	void print();
	void print(Node*);
	void rotate(Node*);
	void doubleRotate(Node*);
	void insert(Node*, Node*);
	Node* search(int);
	Node* remove(Node*, int);
	void remove(int);
	Node* removeMin(Node*, Node*);
	void checkBalance(Node*);
	int findHeight();
	int height(Node*);
	Node* leftRight(Node*);
	Node* rightLeft(Node*);
	Node* leftRotate(Node*);
	Node* rightRotate(Node*);
	void insert(int);
	int max(int, int);
	int getCount();
protected:
	int count;
private:
	Node* root;
};

AVLTree::AVLTree() {
	root = NULL;
	count = 0;
}
/************************************************************************
 * *****************			REMOVING 		*************************
 ***********************************************************************/
void AVLTree::remove(int target) {
	remove(root, target);
}
Node* AVLTree::remove(Node* temp, int target) {
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
		checkBalance(root);
	}
	return NULL;
}

Node* AVLTree::removeMin(Node* parent, Node* child) {
	if (child != NULL) {
		if (child->getLC() != NULL) {
			return removeMin(child, child->getLC());
		} else {
			return child;
		}
	}
	return NULL;
}

/************************************************************************
 * ****************		Checking Balance 		*************************
 ***********************************************************************/
void AVLTree::checkBalance(Node* temp) {
	int heightLeft = height(temp->getLC());
	int heightRight = height(temp->getRC());
	int difference = heightLeft - heightRight;
	temp->setHeight(max(heightLeft, heightRight) + 1);
	if (difference > 1) {
		count++;
		Node* tempLC = temp->getLC();
		if (height(tempLC->getLC()) > height(tempLC->getRC())) {
			count++;
			leftRotate(temp);
		} else {
			leftRight(temp);
		}
	}
	if (difference < -1) {
		count++;
		Node* tempRC = temp->getRC();
		if (height(tempRC->getLC()) > height(tempRC->getRC())) {
			count++;
			rightLeft(temp);
		} else {
			rightRotate(temp);
		}
	}
}
/************************************************************************
 * *****************			Insertion 		*************************
 ***********************************************************************/
void AVLTree::insert(int value) {
	if (root == NULL) {
		root = new Node(value);
	} else {
		this->insert(root, new Node(value));
	}
}

void AVLTree::insert(Node* temp, Node* newNode) {
	int newValue = newNode->getValue();
	if (newValue < temp->getValue()) {
		count++;
		if (temp->getLC() == NULL) {
			temp->setLC(newNode);
			newNode->setParent(temp);
			temp->setHeight(1);
		} else {
			insert(temp->getLC(), newNode);
		}
	} else if (newValue > temp->getValue()) {
		count++;
		if (temp->getRC() == NULL) {
			temp->setRC(newNode);
			newNode->setParent(temp);
			temp->setHeight(1);
		} else {
			insert(temp->getRC(), newNode);
		}
	}
	checkBalance(temp);
}
/************************************************************************
 * *****************			Height 		*************************
 ***********************************************************************/
int AVLTree::height(Node* temp) {
	if (temp == NULL) {
		return -1;
	}
	return temp->getHeight();
}

/************************************************************************
 * *****************			Rotations 		*************************
 ***********************************************************************/

Node* AVLTree::leftRight(Node* temp) {
	temp->setLC(rightRotate(temp->getLC()));
	return leftRotate(temp);
}
Node* AVLTree::rightLeft(Node* temp) {
	temp->setRC(leftRotate(temp->getRC()));
	return rightRotate(temp);
}

//Case 1
Node* AVLTree::leftRotate(Node* temp) {
	Node* oldLC = temp->getLC();
	if (temp == root) {
		count++;
		root = oldLC;
		oldLC->setParent(NULL);
	} else {
		Node* tempParent = temp->getParent();
		if (temp->isLC()) {
			tempParent->setLC(oldLC);
		} else {
			tempParent->setRC(oldLC);
		}
		oldLC->setParent(tempParent);
	}
	temp->setParent(oldLC);
	temp->setLC(oldLC->getRC());
	if (oldLC->getRC() != NULL) {
		oldLC->getRC()->setParent(temp);
	}
	oldLC->setRC(temp);
	temp->setHeight(max((height(temp->getRC())), height(temp->getLC())) + 1);
	oldLC->setHeight(max((height(oldLC->getRC())), height(oldLC->getLC())) + 1);
	return oldLC;
}

Node* AVLTree::rightRotate(Node* temp) {
	Node* oldRC = temp->getRC();
	if (temp == root) {
		count++;
		root = oldRC;
		oldRC->setParent(NULL);
	} else {
		Node* tempParent = temp->getParent();
		if (temp->isLC()) {
			tempParent->setLC(oldRC);
		} else {
			tempParent->setRC(oldRC);
		}
		oldRC->setParent(tempParent);
	}
	temp->setParent(oldRC);
	temp->setRC(oldRC->getLC());

	if (oldRC->getLC() != NULL) {
		oldRC->getLC()->setParent(temp);
	}
	oldRC->setLC(temp);
	temp->setHeight(max((height(temp->getRC())), height(temp->getLC())) + 1);
	oldRC->setHeight(max((height(oldRC->getRC())), height(oldRC->getLC())) + 1);
	return oldRC;
}
Node* AVLTree::search(int target) {
	Node* temp = root;
	while (temp != NULL) {
		if (target < temp->getValue()) {
			count++;
			temp = temp->getLC();
		} else if (target > temp->getValue()) {
			count++;
			temp = temp->getRC();
		} else if (target == temp->getValue()) {
			return temp;
		}
	}
	return NULL;
}
/************************************************************************
 * *****************			MISC 		*************************
 ***********************************************************************/
int AVLTree::max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
/************************************************************************
 * *****************			Printing 		*************************
 ***********************************************************************/
void AVLTree::print() {
	print(root);
	std::cout << std::endl;
	std::cout << "Number of Comparisons: " << count << std::endl;
}

void AVLTree::print(Node* temp) {
	BinarySearchTree::print(temp);
}

int AVLTree::getCount(){
	return count;
}

#endif /* AVLTREE_H_ */
