INC_DIR = include


all: hw3

hw3: main.o struct.o variable.o number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o struct.o variable.o number.o -lgtest
else
	g++ -o hw3 main.o struct.o variable.o number.o -lgtest -lpthread
endif

main.o: main.cpp  term.h atom.h variable.h  utStruct.h utVariable.h number.cpp  struct.cpp variable.cpp
	g++ -std=gnu++0x -c main.cpp
struct.o:struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp
variable.o:variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
number.o:number.h number.cpp
	g++ -std=gnu++0x -c number.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
