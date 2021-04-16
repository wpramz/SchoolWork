//============================================================================
// Name        : Project3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "main.h"
using namespace std;

int main(int argc, char *argv[]) {
	try {
		/**************VARIABLE DECLARATION**************/
		string dictFile;
		string inputFile;
		int mispellCountChain = 0;
		int mispellCountQuad = 0;
		ifstream inDictFile;
		ifstream inInputFile;
		string stringVal = "";
		clock_t start, stop;
		double totalTimeChain;
		double totalTimeQuad;
		chainHash* ch1 = new chainHash();
		quadHash* qh1 = new quadHash();

		if (argc < 2) {
			cout << "There are insufficient arguments" << endl;
			throw "Insufficient Arguments";
		}
		/**************OPENING FILES**************/
		dictFile = argv[1];
		inputFile = argv[2];
		inDictFile.open(dictFile.c_str());
		inInputFile.open(inputFile.c_str());

		/**************CHAINED HASH INSERTION**************/
		start = clock();
		while (inDictFile >> stringVal) {
			for (int i = 0, len = stringVal.size(); i < len; i++) {
				// check whether parsing character is punctuation or not
				if (ispunct(stringVal[i])) {
					stringVal.erase(i--, 1);
					len = stringVal.size();
				}
			}
			transform(stringVal.begin(), stringVal.end(), stringVal.begin(),
					::tolower);
			ch1->insert(stringVal);
		}

		/**************CHAINED HASH SPELL CHECK**************/
		while (inInputFile >> stringVal) {
			for (int i = 0, len = stringVal.size(); i < len; i++) {
				// check whether parsing character is punctuation or not
				if (ispunct(stringVal[i])) {
					stringVal.erase(i--, 1);
					len = stringVal.size();
				}
			}
			transform(stringVal.begin(), stringVal.end(), stringVal.begin(),
					::tolower);
			if (!ch1->contains(stringVal)) {
				mispellCountChain++;
			}
		}
		stop = clock();
		totalTimeChain = (stop - start) / (double) CLOCKS_PER_SEC;

		/**************CLEARING/RESETTING FILES**************/
		inDictFile.clear();
		inDictFile.seekg(0, inDictFile.beg);
		inInputFile.clear();
		inInputFile.seekg(0, inInputFile.beg);
		stringVal = "";

		/**************QUAD HASH INSERTION**************/
		start = clock();
		while (inDictFile >> stringVal) {
			for (int i = 0, len = stringVal.size(); i < len; i++) {
				if (ispunct(stringVal[i])) {
					stringVal.erase(i--, 1);
					len = stringVal.size();
				}
			}
			transform(stringVal.begin(), stringVal.end(), stringVal.begin(),
					::tolower);
			qh1->insert(stringVal);
		}

		/**************QUAD HASH SPELL CHECK**************/
		while (inInputFile >> stringVal) {
			for (int i = 0, len = stringVal.size(); i < len; i++) {
				if (ispunct(stringVal[i])) {
					stringVal.erase(i--, 1);
					len = stringVal.size();
				}
			}
			transform(stringVal.begin(), stringVal.end(), stringVal.begin(),
					::tolower);
			if (!qh1->contains(stringVal)) {
				mispellCountQuad++;
			}
		}
		stop = clock();
		totalTimeQuad = (stop - start) / (double) CLOCKS_PER_SEC;
//		ch1->printInternal();
//		qh1->printInternal();

		/**************PRINTING RESULTS**************/
		cout << "*****Misspells*****" << endl;
		cout << "Chain: " << mispellCountChain << endl;
		cout << "Quadratic: " << mispellCountQuad << endl;
		cout << "*****Runtimes*****" << endl;
		cout << "Chain: " << totalTimeChain << endl;
		cout << "Quadratic: " << totalTimeQuad << endl;
		if (totalTimeQuad < totalTimeChain) {
			cout << "Quadratic Probing is more efficient." << endl;
		} else {
			cout << "Chain Hashing is more efficient." << endl;
		}
	} catch (...) {
		cout << "Caught unknown error. Will Exit program now..." << endl;
	}
	return 0;
}
