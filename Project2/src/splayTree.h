/*
 * splayTree.h
 *
 *  Created on: Mar 23, 2019
 *      Author: willi
 */

#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_
#include "AVLTree.h"

class SplayTree: public AVLTree {
public:
	SplayTree();
	void print();
	void print(Node*);
	Node* zig(Node*);
	Node* zigZag(Node*);
	Node* zigZig(Node*);
	Node* search(int);
	void splay(Node*);
	void insert(int);
	void insert(Node*, Node*);
	Node* leftRight(Node*);
	Node* rightLeft(Node*);
	Node* leftRotate(Node*);
	Node* rightRotate(Node*);
	void remove(int);
	Node* remove(Node*, int);
	Node* removeMin(Node*, Node*);
	int getCount();
private:
	Node* root;
	int count;
};
/*********************************************************
 * **************	 CONSTRUCTOR 	**********************
 */
SplayTree::SplayTree() {
	root = NULL;
	count = 0;
}
/*********************************************************
 * **************	 INSERTION	 	**********************
 */
void SplayTree::insert(int value) {
	if (root == NULL) {
		root = new Node(value);
	} else {
		this->insert(root, new Node(value));
	}
}
void SplayTree::insert(Node* temp, Node* newNode) {
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
	splay(newNode);
}
/*********************************************************
 * **************	 SPLAY	 	**********************
 */
void SplayTree::splay(Node* temp) {
	while (temp != root) {
		Node* tempParent = temp->getParent();
		//The target node's parent is the root
		if (tempParent == root) {
			temp = zig(temp);
		}
		//The target node is a right child and parent is a left child
		else if (temp->isLC() && tempParent->isLC()) {
			count++;
			temp = zigZig(temp);
		} else if (temp->isRC() && tempParent->isRC()) {
			count++;
			temp = zigZig(temp);
		}
		//The target node is a left child and parent is a right child
		else if (temp->isLC() && tempParent->isRC()) {
			count++;
			temp = zigZag(temp);
		}
		//The target node is a right child and parent is a left child
		else if (temp->isRC() && tempParent->isLC()) {
			count++;
			temp = zigZag(temp);
		}
	}
}

/************************************************************************
 * ***************	ZIGS/ZAGS AND MORE!! 		*************************
 ***********************************************************************/
Node* SplayTree::zig(Node* temp) {
	if (temp->isLC()) {
		count++;
		temp = leftRotate(temp->getParent());
	} else {
		count++;
		temp = rightRotate(temp->getParent());
	}
	return temp;
}

Node* SplayTree::zigZag(Node* temp) {
	if (temp->isLC()) {
		count++;
		temp = leftRotate(temp->getParent());
		temp = rightRotate(temp->getParent());
	} else {
		count++;
		temp = rightRotate(temp->getParent());
		temp = leftRotate(temp->getParent());
	}
	return temp;
}

Node* SplayTree::zigZig(Node* temp) {
	if (temp->isLC()) {
		count++;
		temp = leftRotate(temp->getParent());
		temp = leftRotate(temp->getParent());
	} else {
		count++;
		temp = rightRotate(temp->getParent());
		temp = rightRotate(temp->getParent());
	}
	return temp;
}
/************************************************************************
 * ***************				ROTATIONS		*************************
 ***********************************************************************/
Node* SplayTree::leftRight(Node* temp) {
	return AVLTree::leftRight(temp);
}
Node* SplayTree::rightLeft(Node* temp) {
	return AVLTree::rightLeft(temp);
}
Node* SplayTree::leftRotate(Node* temp) {
	Node* oldLC = temp->getLC();
	if (temp == root) {
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
	return oldLC;
}
Node* SplayTree::rightRotate(Node* temp) {
	Node* oldRC = temp->getRC();
	if (temp == root) {
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
	return oldRC;
}

/************************************************************************
 * *****************			REMOVAL	 		*************************
 ***********************************************************************/
void SplayTree::remove(int target) {
	search(target);
	remove(root, target);
}
Node* SplayTree::remove(Node*temp, int target) {
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
				count++;
				temp->getParent()->setLC(NULL);
			} else if (temp->isRC()) {
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
Node* SplayTree::removeMin(Node* parent, Node* child) {
	if (child != NULL) {
		if (child->getLC() != NULL) {
			count++;
			return removeMin(child, child->getLC());
		} else {
			return child;
		}
	}
	return NULL;
}
/************************************************************************
 * *****************			PRINT	 		*************************
 ***********************************************************************/
void SplayTree::print() {
	print(root);
	std::cout << std::endl;
	std::cout <<"Number of Comparisons: "<<count<<std::endl;
}

void SplayTree::print(Node* temp) {
	BinarySearchTree::print(temp);
}
/************************************************************************
 * *****************			SEARCH	 		*************************
 ***********************************************************************/
Node* SplayTree::search(int target) {
	Node* temp = root;
	while (temp != NULL) {
		if (target < temp->getValue()) {
			count++;
			temp = temp->getLC();
		} else if (target > temp->getValue()) {
			count++;
			temp = temp->getRC();
		} else if (target == temp->getValue()) {
			splay(temp);
			return temp;
		}
	}
	return NULL;
}
int SplayTree::getCount(){
	return count;
}

#endif /* SPLAYTREE_H_ */
