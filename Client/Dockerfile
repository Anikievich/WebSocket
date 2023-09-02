FROM gcc

LABEL authors="aniki"

RUN apt-get update && apt-get install -y cmake
COPY . /usr/src/Client

WORKDIR /usr/src/Client

RUN pwd && ls && cd build && ls && cmake .. && make && chmod +x Client
WORKDIR /usr/src/Client/build
CMD ["./Client"]