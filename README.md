# bash.c
commands from a text-FILE habe to be executed (by execvp)
run: ./bash commands.txt -e

actual execvp returns -1. the null-pointer after the commands ist not correct at the moment...
input of execvp are commands followed by a NULL-pointer.

