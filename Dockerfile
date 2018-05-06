FROM debian:jessie

RUN apt-get update && apt-get -y install clang nasm make qemu git

RUN apt-get -y install gcc

WORKDIR /root

VOLUME ["/root/"]

CMD ["bash"] 
