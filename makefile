CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o functions.o
EXEC = eshop

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c functions.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f $(OBJ) $(EXEC)
