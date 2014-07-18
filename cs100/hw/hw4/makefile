GCC = g++
FLAGS = -g

default: shell handle_signals testLinkedString
strip: shell_strip handle_signals_strip testLinkedString_strip
shell: shell.cpp
	$(GCC) $(FLAGS) shell.cpp -o shell

handle_signals: handle_signals.cpp
	$(GCC) $(FLAGS) handle_signals.cpp -o handle_signals

shell_strip: shell.cpp
	$(GCC) shell.cpp -o shell

handle_signals_strip: handle_signals.cpp
	$(GCC) handle_signals.cpp -o handle_signals

testLinkedString_strip: testLinkedString.cpp String_strip.o
	$(GCC) testLinkedString.cpp String.o -o testLinkedString

testLinkedString: testLinkedString.cpp String.o
	$(GCC) $(FLAGS) testLinkedString.cpp String.o -o testLinkedString

String.o: String.cpp
	$(GCC) $(FLAGS) -c String.cpp

String_strip.o: String.cpp
	$(GCC)  -c String.cpp


clean:
	rm -f *.o *.out shell handle_signals testLinkedString

print:
	cat String.h String.cpp testLinkedString.cpp
