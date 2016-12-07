#
# Variables
#

# Compiler options
CC = gcc
#CFLAGS = 

# Directories (build)
SRCDIR = src
INCLDIR = include
BUILDDIR = build

# Directories (install)
#DESTDIR = 
PREFIX = /usr/games
INSTTARGET = lpmines

# Extension?
SRCEXT = c

# Specific files
TARGET = bin/a.out
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

#
# Recipes
#

# Build binary from objects
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET)

# Build objects from source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) -I $(INCLDIR) -c -o $@ $<

# Install to /usr/games
.PHONY: install
install: $(TARGET)
	cp $< $(DESTDIR)$(PREFIX)/$(INSTTARGET)

# Uninstall from /usr/games
.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/$(INSTTARGET)
