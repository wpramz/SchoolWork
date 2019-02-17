//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "main.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	try{
		string projFile;
		int steps;
		int value;
		if(argc<2){
			cout<<"there are insufficient arguments"<<endl;
		}
		projFile = argv[1];
		ifstream inFile;
		inFile.open(projFile.c_str());
		inFile>>steps;
		cout<<"These are the steps: "<<steps<<endl;
		List *myList = new List();
		cout<<"/********After Adding*********/";
		for(int i = 0; i<steps; i++){
			//cout<<"Inside for loop: "<<i<<endl;
			inFile >> value;
			myList->add(value);
		}
		inFile>> steps;

		myList->print();
		cout<<"/********After Deleting*********/";
		for(int i = 0; i<steps; i++){
			inFile >> value;
			myList->removeValue(value);
		}
		myList->print();
	}
	catch(...){
		cout<<"Caught unknown error. will exit Program now..."<<endl;
	}

	return 0;
}
