//============================================================================
// Name        : Project1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.h"
using namespace std;

int main(int argc, char *argv[]) {
	try{
		string projFile;
		int size,size2;
		if(argc<2){
			cout<<"There are insufficient arguments"<<endl;
			throw "Insufficient Arguments";
		}
		projFile = argv[1];
		ifstream inFile;
		inFile.open(projFile.c_str());
		inFile>>size;
		int list[size];
		for(int i=0; i< size; i++){
			inFile>>list[i];
		}
		orderedList listOne(size, list);
		mtfList listTwo(size, list);

		inFile>>size2;
		int list2[size2];

		for(int i =0; i<size2; i++){
			inFile>>list2[i];
		}

		clock_t t1 = clock();
		for(int i =0; i<size2; i++){
			listOne.search(list2[i]);
		}
		t1 = clock()-t1;
		clock_t t2 = clock();
		for(int i =0; i<size2; i++){
			listTwo.search(list2[i]);
		}
		t2=clock()-t2;

		double elapsed_One = (double(t1))/CLOCKS_PER_SEC;
		double elapsed_Two = (double(t2))/CLOCKS_PER_SEC;
		cout<<"Time for orderedList: "<<elapsed_One<<endl;
		cout<<"Time for mtfList: "<<elapsed_Two<<endl;
		if(elapsed_One<elapsed_Two){
			cout<<"Retrieving for orderedList is faster."<<endl;
		}
		else{
			cout<<"Retrieving for mtfList is faster."<<endl;
		}
	}
	catch(...){
		cout<<"Caught unknown error. Will Exit program now..."<<endl;
	}
	return 0;
}
