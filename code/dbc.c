/*
   baby rage: On Windows, format specifiers like "%llu" will not work for 64bit integers. To mitigate this problem, one has to use the __mingw_* versions instead or alternatively the __USE_MINGW_ANSI_STDIO macro. Not sure why this isn't turned on by default.

   found it on: https://sourceforge.net/p/mingw-w64/wiki2/gnu%20printf/

*/

#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "dbc.h"
#include "test.h"

int main(int argc, char *argv[]){
    printf("\ndbc - version %s%s \n\n", RELEASE, REVISION);

    /* init args */
    char *filename = "dummy";
    int id = 0;
    char action = 'x';

    if(argc == 1){
        /* TODO: Write help and usage information in a meaningful way */
        /* TODO: No args mean to me run automatic tests, maybe better with -t */
        /* TODO: Make number of tests more configurable */
        /* TODO: Create a test parameter t ? */
        int nb_tests = 10000;
        run_test(nb_tests);
        return 0;
    }
    else if (argc < 3){
        /* TODO: Need a better usage dialog */
        die("USAGE: dbc <dbfile> <action> [action params]");
    }

    filename = argv[1];
    action = argv[2][0];
    char *name = argv[4];
    char *email = argv[5];

    if(argc > 3){
        id = atoi(argv[3]);
    }

    if(id >= MAX_ROWS) die("There's not that many records in the database.");

    FILE *file;
    file = fopen(filename, "r");
    if (!(file) && (action == 'c')) {
        die("File exists && create");
    }

    struct Connection *conn = Database_open(filename, action);

    /* TODO: Need some kind of event loop construct here
       to *really* work with the database */
    Process_action(action, name, email, conn, id);
    Database_write(conn);
    Database_close(conn);

    return 0;
}
