TARGET   = rshell

CC       = g++
# compiling flags here
CFLAGS   = -Wall -Werror -ansi -pedantic

LINKER   = g++ -o
# linking flags here
#LFLAGS   = -Wall -I. -lm

SRCDIR   = src
INCDIR	 = header
OBJDIR   = obj
BINDIR   = bin


SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"
