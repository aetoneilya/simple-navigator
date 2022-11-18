UNAME := $(shell uname -s)

PROJECT_NAME = SimpleNavigator_v1.0


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

MAINSRC=main.cc
MAINOBJ=$(MAINSRC:.cc=.o)
TESTSRC=tests.cc
TESTOBJ=$(TESTSRC:.cc=.o)
ALGSTATICLIB=s21_graph_algorithms.a
ALGLIBSRCDIR=graph_algorithms
GRAPHSTATICLIB=s21_graph.a
GRAPHLIBSRCDIR=graph
MATRIXSTATICLIB=s21_matrix_oop.a
MATRIXLIBSRCDIR=matrix

BUILDDIR=build
EXECUTABLE=result_file

ifeq ($(UNAME), Linux)
TMPEXECUTABLE=$(PROJECT_NAME)
else ifeq ($(UNAME), Darwin)
TMPEXECUTABLE=$(PROJECT_NAME).app/Contents/MacOS/$(PROJECT_NAME)
endif

LCOVEXEC=$(EXECUTABLE).info
REPORTDIR=report

DOCUMENTS_DIR=doc
DOCUMENT_FILE=SimpleNavigator
CONTAINER_DIR=SimpleNavigator_v1.0

.PHONY: all build build_gcc run install uninstall dvi dist tests gcov_report style cpplint leaks clean rebuild

all: run

build: $(MAINOBJ) $(ALGSTATICLIB) $(GRAPHSTATICLIB) $(MATRIXSTATICLIB)
	$(CXX) $^ -o $(EXECUTABLE) $(LDFLAGS)


build_gcc: $(MAINOBJ) $(ALGSTATICLIB) $(GRAPHSTATICLIB) $(MATRIXSTATICLIB)
	$(CXX) $^ -o $(EXECUTABLE) $(LDFLAGS)

run: build
	./$(EXECUTABLE)

$(ALGSTATICLIB):
	cd $(ALGLIBSRCDIR) && \
	make $(ALGSTATICLIB) && \
	cp $(ALGSTATICLIB) ../

$(GRAPHSTATICLIB):
	cd $(GRAPHLIBSRCDIR) && \
	make $(GRAPHSTATICLIB) && \
	cp $(GRAPHSTATICLIB) ../

$(MATRIXSTATICLIB):
	cd $(MATRIXLIBSRCDIR) && \
	make $(MATRIXSTATICLIB) && \
	cp $(MATRIXSTATICLIB) ../

install: build dvi
	mkdir -p $(CONTAINER_DIR)
	cp $(BUILDDIR)/$(TMPEXECUTABLE) $(CONTAINER_DIR)/$(EXECUTABLE)
	mkdir -p $(CONTAINER_DIR)/$(DOCUMENTS_DIR)
	cp $(DOCUMENT_FILE).pdf $(CONTAINER_DIR)/$(DOCUMENTS_DIR)

uninstall:
	rm -rf $(CONTAINER_DIR)

dvi:
	rubber --pdf $(DOCUMENTS_DIR)/$(DOCUMENT_FILE).latex

dist: install
	tar -cvf $(CONTAINER_DIR).tar $(CONTAINER_DIR)

tests: LDFLAGS+=-lgtest
tests: $(TESTOBJ) $(GRAPHSTATICLIB) $(ALGSTATICLIB)
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
	clang-format -i $(shell find . -type f \( -name "*.h" -o -name "*.cc" \) -not -path "./$(BUILDDIR)/*")

style:
	cppcheck --std=c++17 --enable=all --suppress=missingInclude --suppress=unusedFunction -i ./$(BUILDDIR)/ ./
	clang-format -n $(shell find . -type f \( -name "*.h" -o -name "*.cc" \) -not -path "./$(BUILDDIR)/*")

cpplint:
	cpplint --extensions=cc,h --recursive --exclude=./$(BUILDDIR)/ ./

leaks: tests
	CK_FORK=no valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXECUTABLE)

clean:
	rm -rf $(BUILDDIR) $(MAINOBJ) $(TESTOBJ) $(OBJ) $(EXECUTABLE) $(shell find . -name "*.gcno") $(shell find . -name "*.gcda") *.gcov $(LCOVEXEC) $(REPORTDIR) $(DOCUMENT_FILE).* $(CONTAINER_DIR) *.tar

rebuild: clean all

deep_clean: clean
	rm -f *.a
	cd $(ALGLIBSRCDIR) && \
	make clean
	cd $(GRAPHLIBSRCDIR) && \
	make clean
	cd $(MATRIXLIBSRCDIR) && \
	make clean
