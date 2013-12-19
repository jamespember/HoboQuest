CC := clang++
SRCDIR := .
BUILDDIR := build
CFLAGS := -std=c++11 -stdlib=libc++ -g -Wall -Wno-unused-result
TARGET := hobotest

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET): $(OBJECTS)
	@echo " Linking...";
	$(CC) $(CFLAGS) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " CC $<";
	$(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR)/*.o $(BUILDDIR)/*.o $(TARGET)

full: clean $(TARGET)

-include $(DEPS)

.PHONY: clean
