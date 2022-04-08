# multistage build: use plain buster as a build environment
FROM debian:buster AS builder

# need basic GNU toolchain
RUN apt update && apt install -y python3-pip python3-dev build-essential make

FROM debian:buster-slim

# make a normal user to run the challenge as (no running as root!)
RUN groupadd ctfuser && useradd -g ctfuser --create-home ctfuser

WORKDIR /ctf
COPY flag.txt /ctf
COPY repeatingoffense.py /ctf

user ctfuser

ENTRYPOINT ["python3", "/ctf/repeatingoffense.py"]