FROM gcc:latest

RUN apt-get update \
  && apt-get install -y --no-install-recommends cmake \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

RUN git clone --branch=master --depth 1 https://github.com/Snaipe/Criterion \
  && cd Criterion \
  && mkdir build \
  && cd build \
  && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo \
           -DCMAKE_INSTALL_PREFIX=/usr \
           -DCMAKE_INSTALL_LIBDIR=lib \
           .. \
  && make \
  && make install \
  && cd ../../ \
  && rm -rf Criterion

COPY entrypoint.sh /entrypoint.sh

# Code file to execute when the docker container starts up (`entrypoint.sh`)
ENTRYPOINT ["/entrypoint.sh"]

