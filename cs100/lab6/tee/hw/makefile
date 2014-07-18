SOURCES = Coins.cc main.cc
OBJECTS = main.o betterMain.o bestMain.o Coins.o my_ls.o
GCC = g++
FLAGS = -g

default: main betterMain bestMain my_ls
all: main betterMain bestMain my_ls

main: main.o Coins.o
	$(GCC) $(FLAGS) main.o Coins.o -o main

betterMain: betterMain.o Coins.o
	$(GCC) $(FLAGS) betterMain.o Coins.o -o betterMain

bestMain: bestMain.o Coins.o
	$(GCC) $(FLAGS) bestMain.o Coins.o -o bestMain

my_ls: my_ls.o Coins.o
	$(GCC) $(FLAGS) my_ls.o -o my_ls

main.o: main.cc
	$(GCC) $(FLAGS) -c main.cc

betterMain.o: betterMain.cc
	$(GCC) $(FLAGS) -c betterMain.cc

bestMain.o: bestMain.cc
	$(GCC) $(FLAGS) -c bestMain.cc

Coins.o: Coins.cc
	$(GCC) $(FLAGS) -c Coins.cc

my_ls.o: my_ls.cc
	$(GCC) $(FLAGS) -c my_ls.cc

clean:
	rm -f *.o main betterMain bestMain my_ls 
