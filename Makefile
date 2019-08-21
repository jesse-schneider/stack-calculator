build:
	 g++ stack.cpp -c -o stack.o

	 g++ calculator.cpp -c -o calculator.o

	 g++ main.cpp -c -o main.o

	 g++ main.o stack.o calculator.o -o run

	 ./run

