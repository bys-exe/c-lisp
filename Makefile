all: prompt parser

prompt: prompt.c
	$(CC) prompt.c -o prompt -Wall -std=c99 -g -ledit -lm

parser: parser.c
	$(CC) parser.c -o parser lib/mpc.c -Wall -std=c99 -g -lm

