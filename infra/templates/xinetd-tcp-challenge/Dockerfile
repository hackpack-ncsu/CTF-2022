# multistage build: use plain buster as a build environment
FROM debian:buster AS builder

# need basic GNU toolchain
RUN apt update && apt install -y gcc make

# copy in source/Makefile
WORKDIR /build
COPY chal.c /build
COPY Makefile /build

# build the challenge executable
RUN make chal

# multistage build: actually deploy a buster-slim image with artifacts copied from our build environment
FROM debian:buster-slim

# make a normal user to run the challenge as (no running as root!)
RUN groupadd ctfuser && useradd -g ctfuser --create-home ctfuser

# copy in the `chal` executable
WORKDIR /ctf
COPY --from=builder /build/chal /ctf

# run it as our normal user
USER ctfuser
ENTRYPOINT ["/ctf/chal"]
