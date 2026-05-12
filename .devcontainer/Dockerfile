# .devcontainer/Dockerfile
# -----------------------------------------
# Dockerfile; simple docker container 
# intended for c++ programming.
# -----------------------------------------
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noniteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clangd \
    gdb \
    bear \
    git \
    libgtest-dev \
    clang-format \
    valgrind \
    python3-pip \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/googletest && \
    mkdir build && cd build && \
    cmake .. && make && make install

RUN pip3 install cpplint

WORKDIR /workspace
