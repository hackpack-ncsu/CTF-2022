This program overwrites `bool` to provide a subtle bug: any returned address with the last 2
bytes as 0x0000 will evaluate as falsy.
