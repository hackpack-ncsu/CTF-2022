FROM debian:buster AS builder
RUN apt update -y && apt install -y gcc make
COPY pty/ /work
WORKDIR /work
RUN make pty

# multistage build: actually deploy a buster-slim image with artifacts copied from our build environment
FROM debian:buster-slim

# make a normal user to run the challenge as (no running as root!)
RUN groupadd ctfuser && useradd -g ctfuser --create-home ctfuser

# copy in pty executable from builder environment 
COPY --from=builder /work/pty /bin/pty

# copy in challenge files
COPY /root /

# run shell through pty as unprivileged user
USER ctfuser
WORKDIR /home/ctfuser
ENTRYPOINT ["/bin/pty"]
CMD ["-en", "/bin/sh"]
