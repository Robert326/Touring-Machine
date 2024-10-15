build:
	gcc -o tema1 -g main.c functiiBanda.c
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema1
