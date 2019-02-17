//============================================================================
// Name        : Assignment1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int findCandidate(int listA[]);

int main() {

	return 0;
}

int findCandidate(int listA[]){
	if(sizeof(listA)<2){
		if(sizeof(listA)==1){
			return listA[0];
		}
		else{
			return -1;
		}
	}
	int listB[sizeof(listA)];
	int count = 0;
	for(int i =0; i<sizeof(listA); i+=2){
		if(i==sizeof(listA)-1&&count>(sizeof(listA)/2)){
			listB[count] = listA[i];
			count++;
		}
		else if(listA[i]==listA[i+1]){
			listB[count] = listA[i];
			count++;
		}
	}
	return findCandidate(listB);
}


