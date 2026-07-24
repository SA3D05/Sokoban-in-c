FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install compiler, make, and system-wide SDL2 libraries
RUN apt-get update && apt-get install -y \
    clang \
    make \
    pkg-config \
    libsdl2-dev \
    libsdl2-ttf-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    libgl1-mesa-dev \
    x11-xserver-utils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app