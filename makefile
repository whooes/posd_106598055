NAME = hw8

HW_MAIN = mainTest

SHELL_MAIN = mainShell

HEADER_FILE = atom.h variable.h struct.h number.h term.h list.h scanner.h parser.h global.h node.h  \
			  iterator.h exception.h expression.h

OBJECT_FILE = term.o struct.o list.o node.o

TEST_FILE = exception.h expression.h

all: clean $(NAME) shell

shell: $(SHELL_MAIN).o

ifeq (${OS}, Windows_NT)
	g++ -o shell $(SHELL_MAIN).o $(OBJECT_FILE) -lgtest
else
	g++ -o shell $(SHELL_MAIN).o $(OBJECT_FILE) -lgtest -lpthread
endif

$(SHELL_MAIN).o: $(SHELL_MAIN).cpp $(HEADER_FILE) $(OBJECT_FILE)
	g++ -std=c++11 -c $(SHELL_MAIN).cpp

$(NAME): $(HW_MAIN).o
ifeq (${OS}, Windows_NT)
	g++ -o $(NAME) $(HW_MAIN).o $(OBJECT_FILE) -lgtest
else
	g++ -o $(NAME) $(HW_MAIN).o $(OBJECT_FILE) -lgtest -lpthread
endif

$(HW_MAIN).o: $(HW_MAIN).cpp $(HEADER_FILE) $(OBJECT_FILE) $(TEST_FILE)
	g++ -std=c++11 -c $(HW_MAIN).cpp

term.o: term.h term.cpp iterator.h
	g++ -std=c++11 -c term.cpp
struct.o: struct.h struct.cpp iterator.h
	g++ -std=c++11 -c struct.cpp
list.o: list.h list.cpp iterator.h
	g++ -std=c++11 -c list.cpp
node.o: node.h node.cpp
	g++ -std=c++11 -c node.cpp

clean:

ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(NAME) shell
endif
