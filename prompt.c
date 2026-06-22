#include <stdio.h>
#include <stdlib.h>
#include "lib/mpc.c"

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
    mpc_parser_t *Number = mpc_new("number");
    mpc_parser_t *Operator = mpc_new("operator");
    mpc_parser_t *Expr = mpc_new("expr");
    mpc_parser_t *Lispy = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
              " \
                number : /-?[0-9]+(.[0-9]+)?/; \
                operator : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\"; \
                expr : <number> | '(' <operator> <expr>+ ')'; \
                lispy : /^/ <expr>* <operator> <expr>* /$/; \
              ",
              Number, Operator, Expr, Lispy);

    puts("Lispy version 0.0.0.0.1"); // version
    puts("Press Ctrl+c to Exit\n");  // guide

    while (1)
    {
        char *input = readline("lispy> "); // output prompt and take input from user
        add_history(input);                // add input to history
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r))
        {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        }
        else
        {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }
    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    return 0;
}
