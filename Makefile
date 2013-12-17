NAME = hoboquest

_DEPS =
_OBJ = game.o

SDIR = src
ODIR = build

CC = clang
CFLAGS = -std=c99 -O2 -W -g -I.
CXX = clang++
CXXFLAGS = -std=c++0x -stdlib=libc++ -O2 -W -Wno-unused-result -g -I.

DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.hpp init $(DEPS)
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
