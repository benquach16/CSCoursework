GCC = g++
FLAGS = -g

default: itServer itClient conServer conClient

itServer: itServer.cpp
	$(GCC) $(FLAGS) itServer.cpp -o itserver

itClient: itClient.cpp
	$(GCC) $(FLAGS) itClient.cpp -o itclient

conServer: conServer.cpp
	$(GCC) $(FLAGS) conServer.cpp -o conserver

conClient: conClient.cpp
	$(GCC) $(FLAGS) conClient.cpp -o conclient



clean: 
	rm -f conserver conclient itserver itclient
