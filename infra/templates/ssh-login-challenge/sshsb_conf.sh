#!/bin/sh

# This should match the IMAGE_BASE variable in your Makefile
IMAGE_BASE="ctf2021-ssh-login-challenge"

# This is the port the switchboard will listen on/forward to spawned containers
# (i.e., this is the port that you will have Traefik configured to send ingress
# traffic to from the edge/firewall).
OUTER_PORT=41705

# Modify the rest with care; probably only if you need to adjust 
# the "dockeroptions" section of the config file generated...
#---------------------------------------------------------------
VERSION="$1"
INSTALL="$2"
if [ -z "$1" -o -z "$2" ]; then
	echo "usage: $0 VERSION_TAG INSTALL_PATH"
	exit 1
fi

cat >"$INSTALL" <<EOF
[profile:${IMAGE_BASE}]
outerport = ${OUTER_PORT}
container = ${IMAGE_BASE}:${VERSION}
innerport = 22
limit = 20
reuse = false

[dockeroptions:${IMAGE_BASE}]
auto_remove = true
init = true
read_only = true
tmpfs = {"/tmp": "rw,exec,nosuid,size=16M"}
pids_limit = 32
cpu_period = 1000000
cpu_quota = 500000
mem_limit = 100m
EOF
