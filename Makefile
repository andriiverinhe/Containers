CC = gcc
CFLAG = -Wall -Wextra -Werror
CFLAGS_COVERAGE = -fprofile-arcs -ftest-coverage --coverage 
TESTFLAG = -lgtest -lstdc++ -lm -lgtest_main -pthread

SRC = ./src/
LIB_DIR = lib/
TEST_DIR = tests/

DIR_LIST = $(SRC)$(TEST_DIR)test_list/
DIR_QUEUE = $(SRC)$(TEST_DIR)test_queue/
DIR_STACK = $(SRC)$(TEST_DIR)test_stack/
DIR_VECTOR = $(SRC)$(TEST_DIR)test_vector/
DIR_SET = $(SRC)$(TEST_DIR)test_set/
DIR_MAP = $(SRC)$(TEST_DIR)test_map/
DIR_ARRAY = $(SRC)$(TEST_DIR)test_array/
DIR_MULTISET = $(SRC)$(TEST_DIR)test_multiset/
SOURCE = $(DIR_ARRAY)*.cpp $(DIR_MAP)*.cpp $(DIR_LIST)*.cpp $(DIR_QUEUE)*.cpp $(DIR_STACK)*.cpp $(DIR_VECTOR)*.cpp $(DIR_SET)*.cpp $(SRC)$(TEST_DIR)*.cpp $(DIR_MULTISET)*.cpp
OBJ-FILE = *.o

OPEN_CMD = xdg-open
GCOVR = ~/.local/bin/gcovr

test: clean obj-file
	$(CC) $(OBJ-FILE) $(CFLAG) $(TESTFLAG) -o test_exe

run: test
	./test_exe > test_output_info.log

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --log-file="valgrind_output_info.log" ./test_exe

clean: 
	rm -rf *.o test_exe 
	rm -rf *.log
	clear

obj-file: $(SOURCE)
	$(CC) -c $(SOURCE) $(CFLAG) $(TESTFLAG) 