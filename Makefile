CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
LDFLAGS = -lm

SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib
INCLUDE_DIR = include

SRC = $(SRC_DIR)/recurrent.c
OBJ = $(SRC_DIR)/recurrent.o
LIB = $(LIB_DIR)/librecurrent.a

TEST_SRC = $(TEST_DIR)/test.c
TEST_BIN = $(TEST_DIR)/run.exe

MAIN_SRC = main.c
MAIN_BIN = main.exe

.PHONY: all clean test run-main run-test

all: $(MAIN_BIN) $(TEST_BIN)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB): $(OBJ) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ): $(SRC) $(INCLUDE_DIR)/recurrent.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(MAIN_BIN): $(MAIN_SRC) $(LIB)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $@ $(MAIN_SRC) -lrecurrent $(LDFLAGS)

$(TEST_BIN): $(TEST_SRC) $(LIB)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $@ $(TEST_SRC) -lrecurrent $(LDFLAGS)

test: $(TEST_BIN)
	./$(TEST_BIN)

run-main: $(MAIN_BIN)
	./$(MAIN_BIN)

run-test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(MAIN_BIN) $(TEST_BIN)
	rm -f $(SRC_DIR)/*.o $(SRC_DIR)/*.a
	rm -f $(LIB_DIR)

.PHONY: all clean test run-main run-test