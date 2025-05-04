FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -y \
    libsdl2-dev \
    cmake \
    git \
    build-essential \
    g++ \
    gdb \
    python3.10-venv \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash vscode
USER vscode
WORKDIR /home/vscode/app
