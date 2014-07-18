OBJECTS = main.o fork.o String.o testString.o
GCC = g++
FLAGS = -g


default: unix fork testString
all: unix fork testString

unix: unix.o
	$(GCC) $(FLAGS) unix.o -o unix

fork: fork.o
	$(GCC) $(FLAGS) fork.o -o fork

testString: testString.o String.o
	$(GCC) $(FLAGS) testString.o String.o -o testString

unix.o: unix.cpp
	$(GCC) $(FLAGS) -c unix.cpp

fork.o: fork.cpp
	$(GCC) $(FLAGS) -c fork.cpp

testString.o: testString.cpp
	$(GCC) $(FLAGS) -c testString.cpp

String.o: String.cpp
	$(GCC) $(FLAGS) -c String.cpp

clean:
	rm -f *.o testString fork unix
