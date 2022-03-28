FROM debian:buster-slim

#--------- Install usefull tools -----------
RUN apt-get update && apt-get install -y \
  openssh-server \
  git \
  curl \
  vim \
  apt-utils \
  iputils-ping

#--------- SETUP System -----------

# add user 
RUN useradd -ms /bin/bash player1
# username= player1, password= password
RUN echo 'player1:password' | chpasswd

# Config SSH
# Set SSH timeout
RUN mkdir /var/run/sshd

#set timeout to auto-disconnect when idle (see man sshd)
RUN echo 'ClientAliveInterval 60' >>  /etc/ssh/sshd_config
RUN echo 'ClientAliveCountMax 10' >>  /etc/ssh/sshd_config
RUN echo 'TCPKeepAlive no' >>  /etc/ssh/sshd_config

# created fixed keys
RUN ssh-keygen -A

#--------- SETUP USER -----------

USER player1
WORKDIR /home/player1/
# TODO: set up anything that the user can control

#------------- ROOT -------------

USER root
# TODO: set up any restricted things the user has only limited control over (setuid, etc.)

# Setup SSH
EXPOSE 22
# Start SSH Deamon in "not detach" mode, logging to stderr. Once SSH connction breaks the container stops
ENTRYPOINT ["/usr/sbin/sshd", "-D", "-e"]

