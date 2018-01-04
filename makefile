HW_FILE_NAME = mainTest
HW_NAME = hw8
SHELL_FILE_NAME = mainShell
HEADER_FILE = atom.h variable.h struct.h number.h term.h \
		      list.h scanner.h parser.h global.h node.h  \
			  iterator.h exception.h expression.h
OBJECT_FILE = term.o struct.o list.o node.o
UNIT_TEST_FILE = exception.h expression.h


all: $(HW_NAME) shell

shell: $(SHELL_FILE_NAME).o
ifeq ($(OS), Windows_NT)
	g++ -o shell $(SHELL_FILE_NAME).o $(OBJECT_FILE) -lgtest
else
	g++ -o shell $(SHELL_FILE_NAME).o $(OBJECT_FILE) -lgtest -lpthread
endif

$(SHELL_FILE_NAME).o: $(SHELL_FILE_NAME).cpp $(HEADER_FILE) $(OBJECT_FILE)
	g++ -std=gnu++0x -c $(SHELL_FILE_NAME).cpp

$(HW_NAME): $(HW_FILE_NAME).o
ifeq ($(OS), Windows_NT)
	g++ -o $(HW_NAME) $(HW_FILE_NAME).o $(OBJECT_FILE) -lgtest
else
	g++ -o $(HW_NAME) $(HW_FILE_NAME).o $(OBJECT_FILE) -lgtest -lpthread
endif

$(HW_FILE_NAME).o: $(HW_FILE_NAME).cpp $(HEADER_FILE) $(UNIT_TEST_FILE) $(OBJECT_FILE)
	g++ -std=gnu++0x -c $(HW_FILE_NAME).cpp

term.o: term.h term.cpp iterator.h
	g++ -std=gnu++0x -c term.cpp

struct.o: struct.h struct.cpp iterator.h
	g++ -std=gnu++0x -c struct.cpp

list.o: list.h list.cpp iterator.h
	g++ -std=gnu++0x -c list.cpp

node.o: node.h node.cpp
	g++ -std=gnu++0x -c node.cpp

clean:
ifeq ($(OS), Windows_NT)
	del *.o *.exe
else
	rm -f *.o $(HW_NAME) shell
endif
