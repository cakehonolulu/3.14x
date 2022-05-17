# Setup the Compiler
CC = clang

# Setup the basic compilation flags
# Warn all, extra and compile for c2x
CFLAGS := -Wall -Wextra -pedantic -std=c2x -I.

BINARY := 314x

ifdef WIN
CC = x86_64-w64-mingw32-gcc
endif

ifdef DEBUG
CFLAGS += -g
endif

ifdef ASAN
CFLAGS += -fsanitize=address
endif

all: clean $(BINARY)

$(BINARY): 314x.c engine.c
	@echo "🚧 Building..."
	$(CC) $(CFLAGS) $^ -o $@

clean:
	-@rm -f $(BINARY)
