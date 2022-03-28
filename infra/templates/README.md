# Challenge Templates

Once you have a challenge concept solidified and (hopefully) a working proof-of-concept prototype, you need to package the challenge in a standardized way so it can run smoothly and reliably on our CTF infrastructure.
This directory contains several example challenge templates illustrating our "best practices" for making challenge builds and deployments consistent, streamlined, and robust/reliable in the face of crazy contestant behavior.

## Baseline Requirements

You don't have to use ANY of these templates, as long as you get your challenge working on the infrastructure per the guidance of the organizers/admins.
But you do **have** to provide the following in your challenge, period:

* a `Makefile` so that anyone can update/deploy your challenge with a `git pull && make && sudo make install` inside your challenge's subdirectory of the CTF-2021 `git` repo *(see the templates for examples of such a `Makefile`)*

* a `challenge.json` file providing essential user-facing metadata about your challenge (name, category, description, points, ...); fill out the provided template `challenge.json` file and keep it in your challenge's root subdirectory

## Provided Templates

* `xinetd-tcp-challenge`: basic TCP socket server challenge packaged as a Docker container and deployed on-demand via `xinetd`
* `xinetd-pty-challenge`: variant of `xinetd-tcp-challenge` better for giving contestants an interactive shell experience (as part of the challenge, not post-exploit)
* `ssh-loginc-challenge`: a more heavy-weight system for providing full SSH login experience for shell-based challenges (borrowed from OverTheWire's wargame infrastructure)
* `docker-compose-challenge`: the most general template for running long-lived (i.e., not on-demand) Dockerized services (e.g., web apps)

