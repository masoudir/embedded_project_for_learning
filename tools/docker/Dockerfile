FROM ubuntu:22.04

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    apt-utils \
    coreutils \
    make \
    cmake \
    gcc-arm-none-eabi \
    gdb-arm-none-eabi \
    gcc \
    gdb \
    gdb-multiarch \
    openocd \
    libcmocka-dev \
    gcovr \
    gawk \
    git \
    python3 \
    python3-pip \
    curl \
    wget \
    doxygen \
    graphviz \
    rsync \
    clangd \
    dirmngr \ 
    gnupg \
    apt-transport-https \
    ca-certificates \
    software-properties-common \
    default-jre \
    default-jdk \
    gedit    

# Install python modules
ADD tools/Python/requirements.txt .
RUN pip3 install -r requirements.txt

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=
