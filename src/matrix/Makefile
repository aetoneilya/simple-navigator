CXX=g++
CFLAGS=-c -Wall -Wextra -Werror -std=c++17
LDFLAGS=-lm -lgtest -lpthread

LIBSRC=$(wildcard *.cc)
LIBOBJ=$(LIBSRC:.cc=.o)

STATICLIB=s21_matrix_oop.a

.PHONY: all clean

all: $(STATICLIB)

%.o: %.cc
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o $(STATICLIB)

$(STATICLIB): $(LIBOBJ)
	ar rcs $@ $^

