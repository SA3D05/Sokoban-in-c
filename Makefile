# Compiler
CC = clang

# Headers and libraries
HEADERS = -I/home/satifi/sdl/local/include/SDL2
LIBS    = -L/home/satifi/sdl/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# Sources
SRC = background.c globals.c init_map.c player_movment.c tools.c textures.c main.c

# Object files
OBJ = $(SRC:.c=.o)

# Target program
TARGET = app

# Default rule
all: $(TARGET)
	./app
# Link objects
$(TARGET): $(OBJ) gamelib.h
	$(CC) $(OBJ) -o $(TARGET) $(HEADERS) $(LIBS)

# Compile source files to object files
%.o: %.c
	$(CC) -c $< -o $@ $(HEADERS)

# Clean
clean:
	rm -f $(OBJ)
