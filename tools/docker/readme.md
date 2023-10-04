# Prepare docker for building your codes

## Build docker image

    cd tools/docker
    docker build -t stm32_image:latest .

## Build docker volume

    docker volume create stm32_volume    

## Bringing up docker container

In windows:

* Create this folder: "C:\workspaces\"

Then:

    cd tools/docker/for_windows
    docker compose up -d

In Linux:

* Create this folder by using:

    mkdir $HOME/workspaces

    cd tools/docker/for_linux
    docker compose up -d

## Close down docker container

    docker compose down  