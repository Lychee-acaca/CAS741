#!/bin/bash

# Define the image name and tag
IMAGE_NAME="rwave-dev"
TAG="latest"

# Define the container name
CONTAINER_NAME="rwave-container"

# Get the parent directory of this script (project directory)
PROJECT_DIR=$(dirname "$(realpath "$0")")/..

# Check if the container already exists. If it does, remove the old container
docker ps -a | grep ${CONTAINER_NAME} &> /dev/null
if [ $? -eq 0 ]; then
    echo "Container ${CONTAINER_NAME} already exists, removing the old container..."
    docker rm -f ${CONTAINER_NAME}
fi

# Start the container and mount the project directory
docker run --rm -it --name ${CONTAINER_NAME} -v ${PROJECT_DIR}:/workspace/rwave ${IMAGE_NAME}:${TAG} /bin/bash
