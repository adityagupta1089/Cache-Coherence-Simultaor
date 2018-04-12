IDIR=include
SDIR=src
ODIR=bin

CC=g++
CFLAGS=-I $(IDIR) -std=c++11 -g#-Wall -Wextra -pedantic

DEPS = $(wildcard $(IDIR)/*.hpp)

_SOURCES = $(wildcard $(SDIR)/*.cpp)
SOURCES = $(filter-out $(SDIR)/main.cpp, $(_SOURCES))
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst $(SDIR)/%, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
all: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core