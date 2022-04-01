# multistage build: use plain buster as a build environment
FROM debian:buster AS builder

# need basic GNU toolchain
RUN apt update && apt install -y gcc make git

# copy in source/Makefile
WORKDIR /build
COPY source/main.c /build
COPY Makefile /build

# build the challenge executable
RUN make

# multistage build: actually deploy a buster-slim image with artifacts copied from our build environment
FROM debian:buster-slim

# make a normal user to run the challenge as (no running as root!)
RUN groupadd ctfuser && useradd -g ctfuser --create-home ctfuser

# copy in the `chal` executable and flag
WORKDIR /ctf
COPY --from=builder /build/packshell /ctf
COPY source/flag.txt /ctf

# run it as our normal user
USER ctfuser
ENTRYPOINT ["/ctf/packshell"]
