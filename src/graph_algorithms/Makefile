CXX=g++
CFLAGS=-c -Wall -Wextra -Werror -std=c++17
LDFLAGS=-lm -lgtest -lpthread

LIBSRC=$(wildcard *.cc tsm/*.cc)
LIBOBJ=$(LIBSRC:.cc=.o) #s21_graph.a

STATICLIB=s21_graph_algorithms.a

.PHONY: all clean

all: $(STATICLIB)

%.o: %.cc
	$(CXX) $(CFLAGS) $^ -o $@

s21_graph.a:
	cd ../graph && \
	make s21_graph.a && \
	cp s21_graph.a ../graph_algorithms/

clean:
	rm -rf $(LIBOBJ) $(STATICLIB)

$(STATICLIB): $(LIBOBJ)
	ar rcs $@ $^

