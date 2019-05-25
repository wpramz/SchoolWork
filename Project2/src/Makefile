


p2: main.o
	g++ main.o
	mv a.out p2

main.o: main.cpp main.h AVLTree.h binarySearchTree.h node.h splayTree.h
	g++ -std=c++11 -c main.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip main.cpp main.h AVLTree.h binarySearchTree.h node.h splayTree.h Makefile CoverLetter.docx

clean:
	rm -f *.o p2 core
