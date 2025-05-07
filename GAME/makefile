TARGET = bin/game
SRCS = $(wildcard src/plugins/*.c) src/main.c

OBJS = $(SRCS:.c=.o)

TARGET2 = bin/tests/tests
SRCS2 = src/tests/test_unitaire.c src/plugins/fileprio.c src/plugins/astar.c src/plugins/carte.c

OBJS2 = $(SRCS2:.c=.o)

# Compilation
CC = gcc
CFLAGS = -std=gnu11 -Wall -pedantic -O3

# Debug
CFLAGS += -g
CFLAGS += -fsanitize=address -fno-omit-frame-pointer 
LDFLAGS += -fsanitize=address -lm

# Libs
CFLAGS += $(shell pkg-config --cflags sdl2 SDL2_image SDL2_gfx SDL2_mixer SDL2_ttf)
LDFLAGS += $(shell pkg-config --libs sdl2 SDL2_image SDL2_gfx SDL2_mixer SDL2_ttf)

# Default target
all: $(TARGET)

# Target for running the game
run: $(TARGET)
	./bin/game

# Target for running the tests
test: $(TARGET2)
	./bin/tests/tests

# Linkage for game target
$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

# Linkage for tests target
$(TARGET2): $(OBJS2)
	$(CC) $^ $(LDFLAGS) -o $@

# Compilation rule for .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(OBJS2) $(TARGET) $(TARGET2)
