#!/bin/bash

IMAGE_NAME="rwave-dev"
TAG="latest"

echo "Building Docker image: ${IMAGE_NAME}:${TAG} ..."
docker build -t ${IMAGE_NAME}:${TAG} .

if [ $? -eq 0 ]; then
    echo "Docker image built successfully: ${IMAGE_NAME}:${TAG}"
else
    echo "Docker image build failed"
    exit 1
fi
