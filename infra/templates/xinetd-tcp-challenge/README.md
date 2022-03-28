# Challenge Template: Basic xinetd TCP Service

Many `pwn` and `crypto` challenges involve using `nc` or a similar networking tool to iteract with a simple network server listening on a published TCP port.

This template shows how to create a Dockerized TCP server that can be invoked on the fly, per-TCP-connection by the `xinetd` daemon.

Your Dockerfile must execute a program that reads from `stdin` and writes to `stdout`.
`xinetd` will handle the TCP connection, will launch an instance of your containerized challenge, and will pass the connected socket to your running program as `stdin`/`stdout` (i.e., you don't put any network service code in your challenge program).

*If your challenge requires more sophisticated network lifecycles, like interactions between 2 simultaneous connections to the server, you should not use this template.  Check out the `docker-compose-challenge` template instead.*


## For Challenge Authors

The provided `Dockerfile` is a good one to start from *if* your challenge is written in C/C++.
It combines `Makefile` rules for local testing without xinetd and a multi-stage Docker build that uses the same `Makefile` for maximum consistency.
However, if you are writing a challenge in Python/etc., you should use a more appropriate `Dockerfile` template.

What *is* necessary for the `xinetd` template to work is that your docker container runs a process that communicates bidirectionally (i.e., does socket comms) on the stdin/stdout file descriptors (which is where `xinetd` will put the connected socket when it starts up your container).

The example "challenge" contained in this template is a simple C program to demonstrate the necessity of proper error handling during I/O inside these containers (see the comments in `chal.c`).
It also demonstrates how to pass in build parameters (like the desired FLAG string) as C macro definitions from the `Makefile`, which can be nifty.
If you aren't using C (or if you are but are doing the build differently), just rip out the `chal` and `test` and `clean` rules to declutter the `Makefile`

Update the `IMAGE_BASE` and `SRC_SUBTREE` tuning variables in `Makefile` per the comments.
You can also use the `FLAG` variable to set the flag text in the `Makefile` if you are using the provided build process for your challenge.  Otherwise just delete it to declutter your `Makefile`.

Update the `IMAGE_BASE` and `OUTER_PORT` tuning variables in `xinetd_conf.sh` per the comments.
You may also want to tweak the `xinetd` limits and `docker-run` parameters to suit your challenge particulars.
Note that the default `docker-run` parameters provided in the template are pretty aggressively locked down, for good reason (these are *hackers* we're up against here).
Check with a veteran organizer before loosening these up.

Test, test, and test again!  If everything is correct, you should be able to update things on the live servers with a simple `git pull && make && sudo make install` inside your challenge subdirectory of the repo.

## For Infrastructure Admins

Make sure `xinetd` is running.
