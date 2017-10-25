INC_DIR = include

Name = hw4

all: $(Name)

${Name}: main.o struct.o variable.o number.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o $(Name) main.o struct.o variable.o number.o list.o -lgtest
else
	g++ -o $(Name) main.o struct.o variable.o number.o list.o -lgtest -lpthread
endif

main.o: main.cpp term.h atom.h utList.h
	g++ -std=gnu++0x -c main.cpp
struct.o:struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp
variable.o:variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
number.o:number.h number.cpp
	g++ -std=gnu++0x -c number.cpp
list.o:list.h list.cpp
	g++ -std=gnu++0x -c list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(Name)
endif
