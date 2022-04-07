# multistage build: use plain buster as a build environment
FROM rust:1.59.0-buster AS builder

# copy in source/Makefile
WORKDIR /build
COPY Makefile Cargo.toml Cargo.lock /build/
COPY /src/ /build/src/

# build the challenge executable
RUN make bin/bf-jit

# multistage build: actually deploy a buster-slim image with artifacts copied from our build environment
FROM debian:buster-slim

# make a normal user to run the challenge as (no running as root!)
RUN groupadd ctfuser && useradd -g ctfuser --create-home ctfuser

# copy in the `chal` executable
WORKDIR /ctf
COPY --from=builder /build/bin/bf-jit /ctf/chal
COPY flag.txt /ctf/

# run it as our normal user
USER ctfuser
ENTRYPOINT ["/ctf/chal"]
