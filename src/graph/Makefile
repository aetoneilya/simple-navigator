CXX=g++
CFLAGS=-c -Wall -Wextra -Werror -std=c++17
LDFLAGS=-lm -lgtest -lpthread

LIBSRC=$(wildcard *.cc)
LIBOBJ=$(LIBSRC:.cc=.o) #s21_matrix_oop.a

STATICLIB=s21_graph.a

.PHONY: all clean

all: $(STATICLIB)

%.o: %.cc
	$(CXX) $(CFLAGS) $^ -o $@

s21_matrix_oop.a:
	cd matrix && \
	make s21_matrix_oop.a && \
	cp s21_matrix_oop.a ../

clean:
	rm -rf $(LIBOBJ) $(STATICLIB)

$(STATICLIB): $(LIBOBJ)
	ar rcs $@ $^

