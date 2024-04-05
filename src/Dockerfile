# Исправить
FROM ubuntu:latest

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

ARG BRANCH_OR_TAG=main
ARG CMAKE_OPTIONS=
ENV DEBIAN_FRONTEND=noninteractive
RUN env \
  && apt-get update \
  && apt-get install -q -y git cmake make g++ gcc valgrind libgtest-dev build-essential lcov\
      gettext-base jq curl \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

RUN git clone --depth=1 -b $BRANCH_OR_TAG -q https://github.com/google/googletest.git /googletest
RUN mkdir -p /googletest/build
WORKDIR /googletest/build
RUN cmake .. ${CMAKE_OPTIONS} && make && make install
RUN mkdir -p /code
WORKDIR /code

COPY . .
RUN find  /  -name *gtest* >> txt.txt
RUN cp /googletest/build/lib/libgtest_main.a .
RUN cp /usr/lib/aarch64-linux-gnu/libgtest.a .
RUN  cp /usr/lib/aarch64-linux-gnu/*.a  .

ENTRYPOINT  make matrix_oop.a    && make test
#&& make gcov_report && chmod 777 ./report && make leak && cat leak.log && echo "OK-OK"
