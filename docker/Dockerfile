FROM debian:stable

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-venv \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /workspace/venv

RUN /workspace/venv/bin/pip install cpplint

RUN echo "export PATH=/workspace/venv/bin:$PATH" >> ~/.bashrc

WORKDIR /workspace/rwave

CMD ["/bin/bash"]
