#define the compiler-executable path for hw4
COMPILE = gcc $(COMPILE_SWITCHES)
COMPILE_SWITCHES = -g
OFILES = maze.o main.o solve.o queue.o stack.o

run: $(OFILES)
	$(COMPILE) -o run $(OFILES)

maze.o: maze.c maze.h stack.h queue.h
	$(COMPILE) -c maze.c

main.o: main.c maze.h
	$(COMPILE) -c main.c

solve.o: solve.c maze.h queue.h stack.h
	$(COMPILE) -c solve.c

queue.o: queue.c queue.h 
	$(COMPILE) -c queue.c

stack.o: stack.c stack.h maze.h
	$(COMPILE) -c stack.c

# this defines the command for cleaning up
# all generated files
clean:
	/bin/rm -f *.o solve
