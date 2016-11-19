#
# Variables
#

# Compiler options
CC = gcc
#CFLAGS = 

# Directories
SRCDIR = src
INCLDIR = include
BUILDDIR = build

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
