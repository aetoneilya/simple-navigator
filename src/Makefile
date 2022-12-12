PROJECT_NAME = SimpleNavigator

CXX=g++
CXXFLAGS=-c -pedantic -Wall -Wextra -Wshadow -Wconversion -Wunreachable-code -std=c++17
LDFLAGS=-lm -lpthread

DEBUG ?= 1

ifeq ($(DEBUG),1)
	CXXFLAGS+=-g
	CXXFLAGS+=-DDEBUG
else
	CXXFLAGS+=-O2
	CXXFLAGS+=-Werror
endif

GRAPHSTATICLIB=s21_graph.a
GRAPHLIBSRCDIR=graph
ALGSTATICLIB=s21_graph_algorithms.a
ALGLIBSRCDIR=graph_algorithms
MATRIXSTATICLIB=s21_matrix_oop.a
MATRIXLIBSRCDIR=matrix
CONTAINERSSTATICLIB=s21_containers.a
CONTAINERSLIBSRCDIR=containers

MAINSRC=main.cc
MAINOBJ=$(MAINSRC:.cc=.o)
TESTSRC=tests.cc
TESTOBJ=$(TESTSRC:.cc=.o)
SRC=$(filter-out ./$(MAINSRC) ./$(TESTSRC), $(shell find . -type f -name "*.cc" -not -path "./$(GRAPHLIBSRCDIR)/*" -not -path "./$(ALGLIBSRCDIR)/*" -not -path "./$(MATRIXLIBSRCDIR)/*"))
OBJ=$(SRC:.cc=.o)

EXECUTABLE=result_file

LCOVEXEC=$(EXECUTABLE).info
REPORTDIR=report

.PHONY: all build run tests gcov_report style cpplint leaks clean rebuild

all: run

build: $(MAINOBJ) $(OBJ) $(GRAPHSTATICLIB) $(ALGSTATICLIB) $(MATRIXSTATICLIB)  $(CONTAINERSSTATICLIB)
	$(CXX) $(MAINOBJ) $(OBJ) \
	$(GRAPHLIBSRCDIR)/$(GRAPHSTATICLIB) $(ALGLIBSRCDIR)/$(ALGSTATICLIB) \
	$(MATRIXLIBSRCDIR)/$(MATRIXSTATICLIB) $(CONTAINERSLIBSRCDIR)/$(CONTAINERSSTATICLIB) \
	-o $(EXECUTABLE) $(LDFLAGS)

run: build
	./$(EXECUTABLE)

$(GRAPHSTATICLIB):
	cd $(GRAPHLIBSRCDIR) && \
	make $(GRAPHSTATICLIB)

$(ALGSTATICLIB):
	cd $(ALGLIBSRCDIR) && \
	make $(ALGSTATICLIB)

$(MATRIXSTATICLIB):
	cd $(MATRIXLIBSRCDIR) && \
	make $(MATRIXSTATICLIB)

$(CONTAINERSSTATICLIB):
	cd $(CONTAINERSLIBSRCDIR) && \
	make $(CONTAINERSSTATICLIB)

tests: LDFLAGS+=-lgtest
tests: $(TESTOBJ) $(OBJ) $(GRAPHSTATICLIB) $(ALGSTATICLIB) $(MATRIXSTATICLIB) $(CONTAINERSSTATICLIB)
	$(CXX) $^ -o $(EXECUTABLE) $(LDFLAGS)
	./$(EXECUTABLE)

gcov_report: CXXFLAGS+=--coverage
gcov_report: LDFLAGS+=--coverage
gcov_report: tests
	lcov -t $(EXECUTABLE) -o $(LCOVEXEC) -c -d .
	lcov -r $(LCOVEXEC) "/usr*" -o $(LCOVEXEC)
	genhtml -o $(REPORTDIR) $(LCOVEXEC)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

format:
	clang-format -i $(shell find . -type f \( -name "*.h" -o -name "*.cc" \))

style:
	cppcheck --std=c++17 --enable=all --suppress=missingInclude --suppress=unusedFunction ./
	clang-format -n $(shell find . -type f \( -name "*.h" -o -name "*.cc" \))

cpplint:
	cpplint --extensions=cc,h --recursive ./

leaks: tests
	CK_FORK=no valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXECUTABLE)

clean:
	cd $(GRAPHLIBSRCDIR) && make clean
	cd $(ALGLIBSRCDIR) && make clean
	cd $(MATRIXLIBSRCDIR) && make clean
	cd $(CONTAINERSLIBSRCDIR) && make clean
	rm -rf $(MAINOBJ) $(TESTOBJ) $(OBJ) $(EXECUTABLE) \
	$(shell find . -name "*.gcno") $(shell find . -name "*.gcda") \
	*.gcov $(LCOVEXEC) $(REPORTDIR) $(CONTAINER_DIR) *.tar

rebuild: clean all
