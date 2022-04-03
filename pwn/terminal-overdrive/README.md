This program mimics a miniature shell-like program that takes in user input, executes it, and 
returns.

It comes with a somewhat hidden buffer overflow through the command line arguments. This is because 
it can be started in different 'modes,' and the processing of these arguments is not properly
bounds-checked.