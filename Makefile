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
 
-include $(DEPS)
 
$(TARGET): $(OBJECTS)
	@echo " Linking...";
	$(CC) $(CFLAGS) $^ -o $(TARGET)
 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<";
	$(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<
 
clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)

full: clean $(TARGET)

test: $(TARGET)
	./$(TARGET) test
 
.PHONY: clean test

