# Challenge Template: docker-compose services

Challenges that need to maintain common, persistent state across multiple client connections require running daemons, not on-demand handlers like `xinetd` or `ssh-switchboard`.

This template illustrates using `docker-compose` to orchestrate persistent, robust, hardened daemons (e.g., web servers) for such challenges.

**TODO**

*Don't forget to mention the shared-state problem: we run multiple instances of everything across the redundant servers.  Web apps either need special logic to share a single database server (and accept the SPOF therein) or make do with Traefik "sticky-sessions" and deal with whatever confusion can result there.*
