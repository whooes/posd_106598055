Name = hw6

all: $(Name)

${Name} :	 main.o term.o

ifeq	(${OS}, Windows_NT)
	g++ -o $(Name) main.o term.o -lgtest
else
	g++ -o $(Name) main.o term.o -lgtest -lpthread
endif

main.o: main.cpp term.h atom.h number.h utParser.h struct.h list.h global.h scanner.h parser.h node.h
	g++ -std=gnu++0x -c main.cpp
term.o: term.cpp term.h variable.h
	g++ -std=gnu++0x -c term.cpp


clean:

ifeq (${OS}, Window_NT)
	del *.o *.exe
else
	rm -f *.o $(Name)
endif
