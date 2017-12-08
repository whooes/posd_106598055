Name = hw7

all: $(Name)

${Name} :	 main.o term.o struct.o list.o

ifeq	(${OS}, Windows_NT)
	g++ -o $(Name) main.o term.o struct.o list.o -lgtest
else
	g++ -o $(Name) main.o term.o struct.o list.o -lgtest -lpthread
endif

main.o: main.cpp term.h atom.h number.h utIterator.h global.h scanner.h parser.h node.h
	g++ -std=gnu++0x -c main.cpp
term.o: term.cpp term.h variable.h iterator.h
	g++ -std=gnu++0x -c term.cpp
struct.o: struct.cpp struct.h iterator.h
	g++ -std=gnu++0x -c struct.cpp
list.o: list.cpp list.h iterator.h
	g++ -std=gnu++0x -c list.cpp

clean:

ifeq (${OS}, Window_NT)
	del *.o *.exe
else
	rm -f *.o $(Name)
endif
