CC := clang++
TARGET := hoboquest
SRCDIR := src
BUILDDIR := build
CFLAGS := -std=c++11 -g -Wall -Wno-unused-result

ifeq ($(shell uname -s),Darwin)
CFLAGS += -stdlib=libc++
endif

# Build with test suite
CFLAGS += -DTESTS

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

# Default target (order important)
all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJECTS)
	@echo " Linking...";
	$(CC) $(CFLAGS) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo " CC $<";
	$(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

full: clean $(TARGET)

test: $(TARGET)
	./$(TARGET) test

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean test

