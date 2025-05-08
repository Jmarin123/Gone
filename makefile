CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ = gone.o utility.o lexer.o
TARGET = gone

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)