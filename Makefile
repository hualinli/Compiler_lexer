CC := clang
SRCDIR := src
BINDIR := bin
INCLUDEDIR := $(SRCDIR)/include
SRCEXT := c
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%.$(SRCEXT),$(BINDIR)/%.o,$(SOURCES))
CFLAGS := -g -Wall -I$(INCLUDEDIR)

TARGET := $(BINDIR)/main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $(TARGET)

$(BINDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning..."
	$(RM) -r $(BINDIR)

run: $(TARGET)
	$(TARGET) input.txt

.PHONY: all clean run