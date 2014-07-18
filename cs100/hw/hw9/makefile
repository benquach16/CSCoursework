GCC = g++
FLAGS = -g -pthread

default: mtClient mtServer

mtServer: mtServer.cpp
	$(GCC) $(FLAGS) mtServer.cpp -o server

mtClient: mtClient.cpp
	$(GCC) $(FLAGS) mtClient.cpp -o client

clean: 
	rm -rf server client thread0 thread1 thread2 thread3 thread4 thread5 thread6 thread7 thread8 thread9
