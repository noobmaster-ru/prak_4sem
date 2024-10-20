CC = gcc
PROG = shell
CFLAGS = -g -Wall 
all: list.o tree.o exec.o $(PROG)
list.o: list.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
tree.o: tree.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
exec.o: exec.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
$(PROG): main.c 
	$(CC) $(CFLAGS) main.c list.o tree.o exec.o -o $(PROG)
clean:
	rm -f *.o $(PROG) 
run:
	 ./$(PROG)
