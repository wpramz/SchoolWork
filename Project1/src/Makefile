


p1: main.o
	g++ main.o
	mv a.out p1

main.o: main.cpp main.h orderedList.h mtfList.h node.h
	g++ -std=c++11 -c main.cpp

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip main.cpp main.h orderedList.h mtfList.h node.h Makefile CoverLetter.docx

clean:
	rm -f *.o p1 core
