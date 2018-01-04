Name = hw8

SHELL_FILE = mainShell

HW_FILE = mainTest

all: clean $(Name) shell

hw8: $(HW_FILE).o term.o struct.o list.o node.o

shell: $(SHELL_FILE).o term.o struct.o list.o node.o

ifeq (${OS}, Windows_NT)
	g++ -o $(Name) $(HW_FILE).o term.o struct.o list.o node.o -lgtest
else
	g++ -o $(Name) $(HW_FILE).o term.o struct.o list.o node.o -lgtest -lpthread
endif

ifeq (${OS}, Windows_NT)
	g++ -o shell $(SHELL_FILE).o term.o struct.o list.o node.o -lgtest
else
	g++ -o shell $(SHELL_FILE).o term.o struct.o list.o node.o -lgtest -lpthread
endif

$(HW_FILE).o: $(HW_FILE).cpp expression.h exception.h exp.h variable.h parser.h scanner.h global.h iterator.h number.h
	g++ -std=c++11 -c $(HW_FILE).cpp

$(SHELL_FILE).o: $(SHELL_FILE).cpp expression.h exception.h exp.h variable.h parser.h scanner.h global.h iterator.h number.h
	g++ -std=c++11 -c $(SHELL_FILE).cpp

term.o: term.cpp term.h iterator.h
	g++ -std=c++11 -c term.cpp
struct.o: struct.cpp struct.h iterator.h
	g++ -std=c++11 -c struct.cpp
list.o: list.cpp list.h term.h iterator.h
	g++ -std=c++11 -c list.cpp
node.o: node.cpp node.h term.h
	g++ -std=c++11 -c node.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(Name) shell
endif
