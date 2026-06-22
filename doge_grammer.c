#include "lib/mpc.h"
int main(int argc, char **argv)
{
    mpc_parser_t *hyper = mpc_new("hyper");
    mpc_parser_t *url = mpc_new("url");
    mpc_parser_t *complete = mpc_new("complete");

    mpca_lang(MPCA_LANG_DEFAULT,
              "                                                                                                         \
    hyper : \"https://\";                                   \
    url : \"www.\" \"buildyourownlisp\" \".com\";                                              \
    complete : <hyper> <url>;                                    \
    ",
              hyper, url, complete);

    mpc_cleanup(3, hyper, url, complete);
    return 0;
}
