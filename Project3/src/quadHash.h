/*
 * quadHash.h
 *
 *  Created on: Apr 25, 2019
 *      Author: willi
 */

#ifndef QUADHASH_H_
#define QUADHASH_H_
#include <vector>
#include "node.h"
#include <string>
#include <cmath>
#include <ctype.h>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class quadHash {
public:
	quadHash();
	bool contains(string);
	bool insert(const string);
	bool remove(const string);
	void printInternal();
private:
	int currentCapacity;
	int size;
	void rehash();
	int findPrimeSize(int);
	int hash(const string);
	double loadFactor = 0.5;
	int factor;
	vector<string> theLists;
};
/************************************************************************
 * *****************		Constructor 		*************************
 ***********************************************************************/
quadHash::quadHash() {
	currentCapacity = 4003900;
	size = 0;
	theLists.resize(currentCapacity);
	factor = 1000;
}
/************************************************************************
 * *****************		Insertion	 		*************************
 ***********************************************************************/
bool quadHash::insert(string input) {
	int location = hash(input);
	int i = 0;
	while (i < factor && theLists[(location + (i * i)) % currentCapacity] != "") {
		i++;
	}
	if (i == factor) {
		return false;
	}
	theLists[(location + (i * i)) % currentCapacity] = input;
	size++;
	if (size > (currentCapacity * loadFactor)) {
		rehash();
	}
	return true;
}

/************************************************************************
 * *****************		Spell Checking 		*************************
 ***********************************************************************/
bool quadHash::contains(string target) {
	int location = hash(target);
	if (theLists[location % currentCapacity] == "") {
		return false;
	} else {
		int i = 0;
		while (i < factor
				&& theLists[(location + (i * i)) % currentCapacity] != target) {
			i++;
		}
		if (i == factor) {
			return false;
		}
		if (theLists[(location + (i * i)) % currentCapacity] == target) {
			return true;
		}
	}
	return false;
}
/************************************************************************
 * *****************			Removal 		*************************
 ***********************************************************************/
bool quadHash::remove(string target) {
	int location = hash(target);
	if (theLists[location % currentCapacity] == "") {
		return false;
	} else {
		if (theLists[location % currentCapacity] == target) {
			theLists[location % currentCapacity] = "";
			return true;
		} else {
			int i = 1;
			int initial = location % currentCapacity;
			int newLoc = initial + (i * i);
			while (i < currentCapacity) {
				if (theLists[newLoc % currentCapacity] != "") {
					theLists[newLoc % currentCapacity] = "";
					size--;
				}
				i++;
				newLoc = initial + (i * i);
			}
		}
	}
	return false;
}

/************************************************************************
 * *****************			Hashing 		*************************
 ***********************************************************************/
int quadHash::hash(string input) {
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
void quadHash::printInternal() {
	for (int i = 0; i < currentCapacity; i++) {
		cout << i << ": ";
		cout << theLists[i];
		cout << ", ";
		if ((i + 1) % 10 == 0) {
			cout << endl;
		}
	}
	cout << "Size: " << size << endl;
	cout << endl;
}
/************************************************************************
 * *****************			Rehash	 		*************************
 ***********************************************************************/
void quadHash::rehash() {
	vector<string> temp;
	for (unsigned int i = 0; i < theLists.size(); i++) {
		if (theLists[i] != "") {
			temp.push_back(theLists[i]);
		}
	}
	theLists.clear();
	size = 0;
	currentCapacity = findPrimeSize(currentCapacity);
	theLists.resize(currentCapacity);
	for (unsigned int i = 0; i < temp.size(); i++) {
		insert(temp[i]);
	}

}
/************************************************************************
 * ************		Prime Number Generator 		*************************
 ***********************************************************************/
int quadHash::findPrimeSize(int oldSize) {
	int potSize = oldSize * 2;
	bool found = true;
	while (true) {
		found = true;
		potSize++;
		for (int i = 3; i < potSize; i++) {
			if (potSize % i == 0) {
				found = false;
			}
		}
		if (found) {
			return potSize;
		}
	}
}
#endif /* QUADHASH_H_ */
