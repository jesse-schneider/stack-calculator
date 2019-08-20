build:
	 g++ stack.cpp -c -o stack.o

	 g++ main.cpp -c -o main.o

	 g++ main.o stack.o -o run

	 ./run

