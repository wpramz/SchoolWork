//============================================================================
// Name        : Project2.cpp
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
		if(argc<2){
			cout<<"There are insufficient arguments"<<endl;
			throw "Insufficient Arguments";
		}
		projFile = argv[1];
		ifstream inFile;
		inFile.open(projFile.c_str());
		string stringVal = "";
//		cout<<"******************Inserting***********"<<endl;
		BinarySearchTree* bst1 = new BinarySearchTree();
		AVLTree* avlt1= new AVLTree();
		SplayTree* sptr1 = new SplayTree();
		while(inFile>>stringVal&&stringVal!="$"){
			int value = stoi(stringVal);
			bst1->insert(value);
			avlt1->insert(value);
			sptr1->insert(value);
		}
		cout<<"Binary Search Tree: ";
		bst1->print();
		cout<<"AVL Tree: ";
		avlt1->print();
		cout<<"Splay Tree:";
		sptr1->print();
		cout<<endl;
//		cout<<"***************Searching***********"<<endl;
		while(inFile>>stringVal&&stringVal!="$"){
			int value = stoi(stringVal);
			bst1->search(value);
			avlt1->search(value);
			sptr1->search(value);
		}
		cout<<"Binary Search Tree: ";
		bst1->print();
		cout<<"AVL Tree: ";
		avlt1->print();
		cout<<"Splay Tree:";
		sptr1->print();
		cout<<endl;
//		cout<<"**********************Removing***********"<<endl;
		while(inFile>>stringVal&&stringVal!="$"){
			int value = stoi(stringVal);
			bst1->remove(value);
			avlt1->remove(value);
			sptr1->remove(value);
		}
		cout<<"Binary Search Tree: ";
		bst1->print();
		cout<<"AVL Tree: ";
		avlt1->print();
		cout<<"Splay Tree:";
		sptr1->print();
		cout<<endl;
		int countBST = bst1->getCount();
		int countAVL = avlt1->getCount();
		int countSplay = sptr1->getCount();

		cout<<"Final Comparisons of Binary Search Tree: "<<countBST<<endl;
		cout<<"Final Comparisons of AVL Tree: "<<countAVL<<endl;
		cout<<"Final Comparisons of Splay Tree: "<<countSplay<<endl;
		if(countBST<countAVL&&countBST<countSplay){
			cout<<"Binary Search Tree is the most efficient"<<endl;
		}
		else if(countAVL<countBST&&countAVL<countSplay){
			cout<<"AVL Tree is the most efficient"<<endl;
		}
		else if(countSplay<countBST&&countSplay<countAVL){
			cout<<"Splay Tree is the most efficient"<<endl;
		}

	}
	catch(...){
		cout<<"Caught unknown error. Will Exit program now..."<<endl;
	}
	return 0;
}
