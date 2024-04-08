CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -c
LDFLAGS = -lstdc++ -lm -lgtest -lpthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage -fno-elide-constructors

PROJECTNAME = my_matrix_oop
SRC_DIR = .
SRC_TEST_DIR = .
OBJ_DIR = obj
OBJ_TEST_DIR = $(addprefix $(OBJ_DIR)/, test)
GCOV_HTML_DIR = report

SRC = $(addsuffix .cc, $(addprefix $(SRC_DIR)/, $(PROJECTNAME)))
SRC_TEST = $(wildcard $(SRC_DIR)/test_*.cc)

LIB = $(addsuffix .a, $(PROJECTNAME))
EXECUTABLE = $(addprefix test_, $(PROJECTNAME))
COVERAGE_INFO = $(addsuffix .info, $(PROJECTNAME))
COVERAGE_NAME = $(addprefix $(OBJ_DIR)/, $(addsuffix .gcda, $(PROJECTNAME)))

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cc=.o))
OBJ_TEST = $(addprefix $(OBJ_TEST_DIR)/, $(SRC_TEST:.cc=.o))
OS := $(shell uname)

all: clean test

clean:
	@echo "Cleaning up..."
	rm -rf *.o $(EXECUTABLE) $(LIB) $(OBJ_DIR) $(GCOV_HTML_DIR)

test: clean ${EXECUTABLE}
	@echo "Running tests..."
	./${EXECUTABLE}

$(LIB): ${OBJ}
	@echo "Building the static library..."
	ar rc $(LIB) $^
	ranlib $(LIB)

$(OBJ): $(SRC)
	@echo "Compiling the library source files..."
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(GCOVFLAGS)

$(OBJ_TEST): $(SRC_TEST)
	@echo "Compiling the tests..."
	@mkdir -p $(OBJ_TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(EXECUTABLE): $(OBJ_TEST) $(LIB)
	@echo "Linking..."
	$(CC) $^ -o $@ $(LDFLAGS) $(GCOVFLAGS)

gcov_report: test
	@echo "Generating HTML coverage report..."
	@mkdir -p $(GCOV_HTML_DIR)
	geninfo $(COVERAGE_NAME) --output-file $(GCOV_HTML_DIR)/$(COVERAGE_INFO)
	genhtml $(GCOV_HTML_DIR)/$(COVERAGE_INFO) -o $(GCOV_HTML_DIR)
	open $(GCOV_HTML_DIR)/index.html

test_memory: $(EXECUTABLE)
	@echo "Checking leaks..."
ifeq ($(OS),Linux)
	valgrind ./$(EXECUTABLE) --check-full
endif
ifeq ($(OS),Darwin) 
	CK_FORK=no leaks -quiet --atExit -- ./$(EXECUTABLE)
endif

test_format:
	@echo "Checking styles..."
	clang-format -n -style=Google *.cc *.h

.PHONY: all clean test gcov_report test_memory test_format
