CC=gcc
CLINK=$(CC)
CFLAGS= -g -Wall -std=c99
OBJS=libgrades.so 
EXEC=prog.exe
RM= rm -rf

$(EXEC) : $(OBJS) liblinked-list.so 
	$(CC) libgrades.so -L/path/to/lib -llinked-list -o prog.exe


libgrades.so: grades.o 
	$(CLINK) -shared grades.o -o libgrades.so 

grades.o: grades.c grades.h linked-list.h 
	$(CLINK) -c -fpic grades.c 


clean:
	$(RM) *.o *.exe
