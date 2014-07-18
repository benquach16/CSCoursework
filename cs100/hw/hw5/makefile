GCC = g++
FLAGS = -g
OBJS = ship.o frigate.o carrier.o dreadnought.o

default: testShips my_shell

strip: testShips my_shell_strip

print: 
	a2ps my_shell.cpp -o my_shell.ps | ps2pdf my_shell.ps shell.pdf

my_shell: my_shell.cpp
	$(GCC) $(FLAGS) my_shell.cpp -o my_shell

my_shell_strip: my_shell.cpp
	$(GCC) my_shell.cpp -o my_shell

testShips: ship.o frigate.o carrier.o dreadnought.o testShips.cpp
	$(GCC) $(FLAGS) testShips.cpp ship.o frigate.o carrier.o dreadnought.o -o testShips


ship.o: ship.h ship.cpp
	$(GCC) $(FLAGS) -c ship.cpp

frigate.o: frigate.h frigate.cpp
	$(GCC) $(FLAGS) -c frigate.cpp

carrier.o: carrier.h carrier.cpp
	$(GCC) $(FLAGS) -c carrier.cpp

dreadnought.o: dreadnought.h dreadnought.cpp
	$(GCC) $(FLAGS) -c dreadnought.cpp



clean:
	rm -f testShips my_shell *.o *.out my_shell.ps shell.pdf
