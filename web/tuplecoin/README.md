# TupleCoin

A combined crypto/web challenge, in which the vulnerability is ambiguous serialization of a “transaction” object before “signing” with a secret key which the players never get/see.

The trick is to realize that two different transactions (“from 123 to 45” vs. “from 12 to 345”) will serialize to the same character sequence (“12345”) and thus produce the same “signature.”

If players use this trick to forge and commit a transaction copying “coins” from the CEO’s published account number (to anyone, actually), they get the flag.

The bug can be discovered by exploiting a "source code backup leak" revealed in `robots.txt` to read the server side code and figure out the serialization/signing loophole.


## Deployment

Should be able to build/deploy by running `make && make install` on the challenge server as a Docker-capable user (i.e., someone in the `docker` group), or `sudo make && sudo make install` otherwise (bad idea, but whatever blows your hair back).

It runs a docker service (restart-always) exposing a single HTTP server bound to a configurable host/port (default: `127.0.0.1`:`8100`).
The host/port binding configuration is in the `Makefile` (change the `HOST` and `PORT` variables).

This web app is _fully_ stateless---there is no database or other server-side state tracking.  So feel free to run multiple parallel instances without worrying about sticky sessions/etc.

