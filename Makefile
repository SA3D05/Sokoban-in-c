# Container Settings
IMAGE_NAME = sdl2-game-env
CONTAINER_APP = /app

# Native Compilation Flags (Used inside the Docker container)
CC      = clang
CFLAGS  = -Wall -Wextra $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_image SDL2_mixer 2>/dev/null)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_image SDL2_mixer 2>/dev/null)

# Project Files
SRC    = background.c globals.c init_map.c player_movment.c tools.c textures.c sounds.c main.c
OBJ    = $(SRC:.c=.o)
TARGET = app

# Docker Execution Wrapper with X11 Display Forwarding
DOCKER_RUN = docker run --rm -it \
	-e DISPLAY=$(DISPLAY) \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-v $(shell pwd):$(CONTAINER_APP) \
	--net=host \
	--device /dev/snd \
	-e PULSE_SERVER=unix:${XDG_RUNTIME_DIR}/pulse/native \
	-v ${XDG_RUNTIME_DIR}/pulse/native:${XDG_RUNTIME_DIR}/pulse/native \
	--group-add audio \
	$(IMAGE_NAME)
.PHONY: all build run docker-build clean fclean re

# Default target: builds image (if needed), compiles inside docker, and runs the game
all: docker-build
	@xhost +local:docker > /dev/null 2>&1 || true
	$(DOCKER_RUN) make run-internal

# Builds the Docker Image only if not already built
docker-build:
	@if [ -z "$$(docker images -q $(IMAGE_NAME) 2> /dev/null)" ]; then \
		echo "Building Docker environment image..."; \
		docker build -t $(IMAGE_NAME) .; \
	fi

# Compiles the executable inside the container
compile:
	$(DOCKER_RUN) make $(TARGET)

# Internal target invoked inside the container to build & execute
run-internal: $(TARGET)
	./$(TARGET)

# Link step (runs inside container)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile C source files (runs inside container)
%.o: %.c gamelib.h
	$(CC) $(CFLAGS) -c $< -o $@

# Cleanup binaries and object files locally
clean:
	rm -f $(OBJ) $(TARGET)

# Remove docker image as well
fclean: clean
	@if [ -n "$$(docker images -q $(IMAGE_NAME) 2> /dev/null)" ]; then \
		docker rmi $(IMAGE_NAME); \
	fi

re: clean all