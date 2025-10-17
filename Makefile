<<<<<<< HEAD
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
=======
CC=gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

SRC = src/iterator.c
OBJ = $(SRC:.c=.o)

TEST_SRC = test/test_iterator.c
TEST_BIN = test/run

LIB = src/iterator.a

all: start

start: $(OBJ) main.o
	$(CC) $(CFLAGS) $(OBJ) main.o -o st
	./st

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o

lib: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Изменено: убрана зависимость от check
test: $(LIB) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB) -o $(TEST_BIN)
	./$(TEST_BIN)

# Изменено: убрана зависимость от check
gcov_report: CFLAGS += $(GCOVFLAGS)
gcov_report: clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $(SRC) -o iterator.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $(TEST_SRC) -o test.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) iterator.o test.o -o $(TEST_BIN)
	./$(TEST_BIN)
	lcov -t "iterator" -o coverage.info -c -d .
	lcov --remove coverage.info "*/test/*" -o coverage.info
	genhtml -o report coverage.info

leaks: test
	leaks --atExit -- ./test/run

clean:
	rm -f st *.gcda *.gcno *.o
	rm -f src/*.o src/*.a src/*.gcno src/*.gcda src/*.gcov coverage.info
	rm -f test/run test/*.o test/*.gcno test/*.gcda test/*.gcov
	rm -rf report

.PHONY: all lib clean test gcov_report leaks
>>>>>>> 48c2ce7b71291195b58adb08b87cb46fdd22493c
