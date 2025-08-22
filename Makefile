CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -lm
TARGET = lagrange_quadratic
SOURCE = lagrange_quadratic.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
