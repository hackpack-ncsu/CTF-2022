FROM python:3-buster

# We need to have the docker tools, and we need to mount the docker socket to spawn sibling containers
RUN pip3 install dumb-init
RUN apt update && apt -y upgrade && apt install -y wget
RUN wget https://download.docker.com/linux/static/stable/x86_64/docker-18.09.2.tgz && tar -C /opt -xf docker-18.09.2.tgz

# Download and install OverTheWire.org's docker-tcp-switchboard project
COPY requirements.txt /app/
WORKDIR /app
RUN pip3 install -r requirements.txt

COPY docker-tcp-switchboard.py requirements.txt /app/

ENTRYPOINT ["/usr/local/bin/dumb-init", "--"]
CMD ["/usr/bin/env", "python3", "/app/docker-tcp-switchboard.py"]
