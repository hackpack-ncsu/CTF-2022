# Infrastructure Services

Our challenge templates depend on a number of insfrastructure services that must be running on all challenge hosting servers.

## System/Packaged Services

Install and activate these services using the host server's package manager/service runner:

* `xinetd`: a modernized `inetd` daemon we use to auto-instantiate per-TCP-connection Docker containers for network-based challenges 

## Custom Services

Build and deploy these services as long-lived Docker container instances:

* `ssh-switchboard`: borrowed from OverTheWire.org's wargames infrastructure, this service auto-deploys a dockerized SSH server for hosting isolated SSH-accessible shell challenges *(challenge authors should check out the `ssh-login-challenge` template to see how to configure such a challenge)*

