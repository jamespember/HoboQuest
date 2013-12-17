# NAME = hoboquest

# _DEPS =
# _OBJ = game.o

# SDIR = src
# ODIR = build

# CC = gcc
# CFLAGS = -std=c99 -O2 -W -g -I.
# CXX = g++
# CXXFLAGS = -std=c++0x -O2 -W -Wno-unused-result -g -I.

# DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# $(ODIR)/%.o: $(SDIR)/%.hpp init $(DEPS)
	# $(CXX) $(CXXFLAGS) -c -o $@ $<

# $(NAME): $(OBJ)
	# $(CXX) $(CXXFLAGS) -o $@ $^

# .PHONY: clean

# init:
	# mkdir -p $(ODIR)

# test: $(NAME)
	# ./test $(NAME)

# full: clean $(NAME)

# clean:
	# rm -f $(ODIR)/*.o
	# rm -f $(NAME).exe
 
CC := clang++
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -Wall -Wno-unused-result
TARGET := hoboquest
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)
 
$(TARGET): $(OBJECTS)
	@echo " Linking...";
	$(CC) $^ -o $(TARGET)
 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<";
	$(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<
 
clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)
 
-include $(DEPS)
 
.PHONY: clean
