# Challenge Template: xinetd TCP Service with pty Support

For challenges that involve `nc`-like TCP connections but which are supposed to invoke an interactive shell (with line editing, etc.) on the other end (as part of the challenge, not as post-exploitation), this variant of the `xinetd` service template includes source code and Dockefile support for a helper program called `pty`.

The `pty` program is a wrapper that launches your actual target binary (which would typically be `/bin/sh` or some other interactive shell), passing it not a socket but a pseudo-TTY (or *pty*) as `stdin`/`stdout`.  This will make the shell behave like a proper interactive shell with line editing/etc.

## For Challenge Authors

All build-customization steps are the same as for the basic `xinetd-tcp-challenge` template.

Note that the provided `docker-run` parameters are slightly looser than for the `xinetd-tcp-challenge` template: the number of allowed processes is higher (32 vs. 4) to allow for shell programs/pipelines to run, and the temporary filesystem is mounted `exec` vs. `noexec` so that the user can run binaries compiled/stored on `/tmp`.

## For Infrastructure Admins

Make sure `xinetd` is running.
