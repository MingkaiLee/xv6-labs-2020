# Author: lmk17@tsinghua.org.cn
# This file will construct a docker image which could do labs.
FROM ubuntu:20.04
RUN apt update
RUN apt-get install -y git build-essential gdb-multiarch gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu
RUN apt-get install -y qemu-system-misc
RUN apt-get install -y python-is-python3
