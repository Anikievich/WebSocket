FROM gcc

LABEL authors="aniki"


RUN apt-get update && apt-get install -y cmake
COPY . /usr/src/Server
EXPOSE 9090

WORKDIR /usr/src/Server


RUN pwd && ls && cd build && ls && cmake .. && make && chmod +x Server
WORKDIR /usr/src/Server/build
CMD ["./Server"]