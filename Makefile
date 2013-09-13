# CC = g++
# CFLAGS = -Wall -g -Wl,--enable-auto-import #-O2

# game:
	# $(CC) $(CFLAGS) -o hoboquest hoboquest/*.h main.cpp

# check:
	# $(CC) $(CFLAGS) -o hobotest test/*.h test/test.cpp

NAME = hoboquest

_DEPS =
_OBJ = game.o

SDIR = src
ODIR = build

CC = gcc
CFLAGS = -std=c99 -O2 -W -g -I.
CXX = g++
CXXFLAGS = -std=c++0x -O2 -W -Wno-unused-result -g -I.

DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.h init $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

init:
	mkdir -p $(ODIR)

test: $(NAME)
	./test $(NAME)

full: clean $(NAME)

clean:
	rm -f $(ODIR)/*.o
	rm -f $(NAME).exe
