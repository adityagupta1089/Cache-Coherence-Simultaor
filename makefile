IDIR=include
SDIR=src
ODIR=bin

CC=g++
CFLAGS=-I $(IDIR) -std=c++11 -Wall -Wextra -pedantic -g

_DEPS = Cache.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

SOURCES = Cache.cpp
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core