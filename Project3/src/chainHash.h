/*
 * chainHash.h
 *
 *  Created on: Apr 18, 2019
 *      Author: willi
 */

#ifndef CHAINHASH_H_
#define CHAINHASH_H_
#include <vector>
#include "node.h"
#include <string>
#include <cmath>
#include <ctype.h>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class chainHash {
public:
	chainHash();
	bool contains(string);
	bool insert(const string);
	bool remove(const string);
	void printInternal();
	vector<Node*> theLists;
	int currentCapacity;
	void rehash();
	int size;
	int hash(const string);
};
/************************************************************************
 * *****************		Constructor 		*************************
 ***********************************************************************/
chainHash::chainHash() {
	currentCapacity = 40039;
	size = 0;
	theLists.resize(currentCapacity);
}
/************************************************************************
 * *****************			Insertion 		*************************
 ***********************************************************************/
bool chainHash::insert(string input) {
	Node* toInsert = new Node(input);
	int location = hash(input);
	if (theLists.at(location % currentCapacity) == NULL) {
		theLists[location % currentCapacity] = toInsert;
		size++;
	} else {
		Node* temp = theLists.at(location % currentCapacity);
		while (temp->getNext() != NULL) {
			temp = temp->getNext();
		}
		temp->setNext(toInsert);
		size++;
	}
	return true;
}
/************************************************************************
 * *****************		Spell Checking 		*************************
 ***********************************************************************/
bool chainHash::contains(string input) {
	int location = hash(input);
	if (theLists.at(location % currentCapacity) == NULL) {
		return false;
	} else {
		Node* temp = theLists.at(location % currentCapacity);
		if (temp->getValue() == input) {
			return true;
		} else {
			while (temp->getNext() != NULL) {
				temp = temp->getNext();
				if (temp->getValue() == input) {
					return true;
				}
			}
		}
	}
	return false;
}
/************************************************************************
 * *****************			Removal 		*************************
 ***********************************************************************/
bool chainHash::remove(string input) {
	int location = hash(input);
	if (theLists.at(location % currentCapacity) == NULL) {
		return false;
	} else {
		Node* temp = theLists.at(location % currentCapacity);
		Node* trailer = temp;
		if (temp->getValue() == input) {
			theLists[location % currentCapacity] = temp->getNext();
			delete temp;
			return true;
		} else {
			while (temp->getNext() != NULL) {
				temp = temp->getNext();
				if (temp->getValue() == input) {
					trailer->setNext(temp->getNext());
					delete temp;
					return true;
				}
				trailer = trailer->getNext();
			}
		}
	}
	return false;
}
/************************************************************************
 * *****************			Hashing 		*************************
 ***********************************************************************/
int chainHash::hash(string input) {
	int loc = 0;
	int multiple = 691;
	for (unsigned int i = 0; i < input.length(); i++) {
		loc += (int(input[i]) * multiple * (2 ^ i));
	}
	return loc;
}
/************************************************************************
 * *****************		Print Internal 		*************************
 ***********************************************************************/
void chainHash::printInternal() {
	Node* temp = new Node();
	for (unsigned int i = 0; i < theLists.capacity(); i++) {
		cout << i << ": ";
		temp = theLists[i];
		while (temp != NULL) {
			cout << temp->getValue();
			temp = temp->getNext();
			cout << ", ";
		}
		cout << ", ";
		if ((i + 1) % 10 == 0) {
			cout << endl;
		}
	}
	cout << "Size: " << size << endl;
	cout << endl;
}
#endif /* CHAINHASH_H_ */
