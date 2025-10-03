CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib
INCLUDE_DIR = include

SRC = $(SRC_DIR)/perm.c
OBJ = $(SRC_DIR)/perm.o
LIB = $(LIB_DIR)/libperm.a

TEST_SRC = $(TEST_DIR)/test.c
TEST_BIN = $(TEST_DIR)/run.exe

MAIN_SRC = main.c
MAIN_BIN = main.exe

.PHONY: all clean test

all: $(MAIN_BIN) $(TEST_BIN)

$(LIB_DIR):
	if not exist $(LIB_DIR) mkdir $(LIB_DIR)

$(LIB): $(OBJ) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ): $(SRC) $(INCLUDE_DIR)/perms.h
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(MAIN_BIN): $(MAIN_SRC) $(LIB)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $@ $(MAIN_SRC) -lperm

$(TEST_BIN): $(TEST_SRC) $(LIB)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $@ $(TEST_SRC) -lperm

test: $(TEST_BIN)
	$(TEST_BIN)

clean:
	del /Q *.exe *.o 2>nul
	del /Q $(SRC_DIR)\*.o $(SRC_DIR)\*.a 2>nul
	del /Q $(TEST_DIR)\*.exe $(TEST_DIR)\*.o 2>nul
	if exist $(LIB_DIR) rmdir /S /Q $(LIB_DIR)