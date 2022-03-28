# Docker-TCP-Switchboard Switch Container

Shamelessly ripped off from [OverTheWire.org](https://github.com/OverTheWireOrg/docker-tcp-switchboard/).
Modified to log to STDERR instead of files only.

## Quick Start

Just do `make && sudo make install` to set up a long-running `ssh-switchboard` Docker container on the current host.

Challenges that use `ssh-switchboard` deployments will auto-restart this Docker container when they are installed (see the `ssh-login-challenge` template `Makefile` for details).

## Original/Internal Documentation

### Building

Make sure the `board.conf` file contains all the intended service/container configurations before doing Docker build.  *(Or else mount something external over `/etc/docker-tcp-switchboard.conf` at launch time.)*

### Running

You *must* run this image with `-v /var/run/docker.sock:/var/run/docker.sock` or it will not be able to spawn containers on connection, and you must also run it with `--net=host` or SSH connections will not pass through to the launched containers!

The first requirement is just the price of docker-in-docker (no user interaction happens directly with this master container, so the security risk should be minimal).

The second requirement should go away if we configure the launched containers right, but I don't have time to do that right now...

