CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

ifeq ($(OS),Windows_NT)
    EXEEXT = .exe
endif

program = practical-calc$(EXEEXT)
objects = main.o calc.o

$(program): $(objects)
	$(CC) $(LDFLAGS) -o $@ $(objects) $(LDLIBS)

main.o calc.o: calc.h

run: $(program)
	./$(program) 41 + 33 111 - 8 22 "*" 5 221 % 111 100 + 13 -k 2

clean:
	$(RM) $(objects) $(program)
