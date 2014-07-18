GCC = g++
FLAG = -g

default: my_shell testMatrix

my_shell: my_shell.cpp
	$(GCC) $(FLAG) my_shell.cpp -o my_shell

testMatrix: main.cpp
	$(GCC) $(FLAG) main.cpp -o testMatrix

clean:
	rm -f testMatrix my_shell
