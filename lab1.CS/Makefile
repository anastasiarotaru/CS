CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGETS = caesar_task1 caesar_task2

.PHONY: all clean run-task1 run-task2 help

all: $(TARGETS)

caesar_task1: caesar_task1.c
	$(CC) $(CFLAGS) -o caesar_task1 caesar_task1.c

caesar_task2: caesar_task2.c
	$(CC) $(CFLAGS) -o caesar_task2 caesar_task2.c

run-task1: caesar_task1
	./caesar_task1

run-task2: caesar_task2
	./caesar_task2

clean:
	rm -f $(TARGETS) *.o

help:
	@echo "Caesar Cipher Laboratory Work - Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Compile all programs"
	@echo "  clean     - Remove compiled files"
	@echo "  run-task1 - Compile and run Task 1.1"
	@echo "  run-task2 - Compile and run Task 1.2"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Usage:"
	@echo "  make           # Compile all"
	@echo "  make run-task1 # Run Task 1.1"
	@echo "  make run-task2 # Run Task 1.2"
	@echo "  make clean     # Clean up"