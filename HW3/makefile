CC=gcc
CLINK=$(CC)
CFLAGS= -g -Wall -std=c99
OBJS=main.o stack.o student.o
EXEC=prog.exe
RM= rm -rf

$(EXEC) : $(OBJS)
	$(CLINK) $(OBJS) -o prog.exe

stack.o: stack.c stack.h

student.o: student.c student.h stack.h

main.o: main.c stack.h student.h


clean:
	$(RM) *.o *.exe