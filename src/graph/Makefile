CXX=g++
CXXFLAGS=-c -pedantic -Wall -Wextra -Wshadow -Wconversion -Wunreachable-code -std=c++17
LDFLAGS=-lm

DEBUG ?= 0

ifeq ($(DEBUG),1)
	CXXFLAGS+=-g
	CXXFLAGS+=-DDEBUG
else
	CXXFLAGS+=-O2
	CXXFLAGS+=-Werror
endif

SRC=$(wildcard *.cc)
OBJ=$(SRC:.cc=.o)
STATICLIB=s21_graph.a

.PHONY: all build clean rebuild $(STATICLIB)

all: build

build: $(STATICLIB)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf *.o $(EXECUTABLE) $(STATICLIB)

rebuild: clean all

$(STATICLIB): $(OBJ)
	ar rcs $@ $^
