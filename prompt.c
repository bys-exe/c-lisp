#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32 // if we are compiling from windows run this
#include <string.h>
static char buffer[2048];
char *readline(char *prompt)
{ // fake readline function we created
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char *cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}
void add_history(char *unused) {} // fake add_history func
#else                             // if using linux/macos run this instead
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char **argv)
{
    puts("Lispy version 0.0.0.0.1"); // version
    puts("Press Ctrl+c to Exit\n");  // guide
    while (1)
    {
        char *input = readline("lispy> "); // output prompt and take input from user
        add_history(input);                // add input to history
        printf("No u are %s\n", input);
        free(input);
    }
    return 0;
}
