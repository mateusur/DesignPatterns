FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
ARG WGET_ARGS="-q --show-progress --progress=bar:force:noscroll"

RUN apt update
RUN apt upgrade -y 
RUN apt install -y --no-install-recommends git cmake ninja-build \
    ccache make gcc gcc-multilib g++-multilib clang clang-format clang-tidy