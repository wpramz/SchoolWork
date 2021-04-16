


p3: main.o
	g++ main.o
	mv a.out p3

main.o: main.cpp main.h node.h quadHash.h chainHash.h
	g++ -std=c++11 -c main.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip main.cpp main.h node.h quadHash.h chainHash.h Makefile CoverLetter.docx

clean:
	rm -f *.o p3 core
