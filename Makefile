CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

all: build/recursive_descent

build/recursive_descent: src/recursive_descent.c
	mkdir -p build
	$(CC) $(CFLAGS) src/recursive_descent.c -o build/recursive_descent

run: all
	./build/recursive_descent

clean:
	rm -rf build *.exe
