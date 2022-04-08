# multistage build: use plain buster as a build environment
FROM python:3 AS builder

# need basic GNU toolchain
# RUN apt update && apt install -y python3-pip python3-dev build-essential make


# make a normal user to run the challenge as (no running as root!)
RUN groupadd ctfuser && useradd -g ctfuser --create-home ctfuser

WORKDIR /ctf
COPY flag.txt /ctf
COPY repeatingoffense.py /ctf
COPY entry.sh /ctf
RUN chmod +x /ctf/entry.sh
RUN chmod +x /ctf/repeatingoffense.py
USER ctfuser
RUN pip3 install pycryptodome

ENTRYPOINT ["/ctf/entry.sh"]