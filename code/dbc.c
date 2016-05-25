#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEBUG 0
#define MAX_DATA 32
#define MAX_ROWS 10

#define RELEASE "0.1"
#define REVISION ".1"

#include "dbc.h"
#include "test.h"

int main(int argc, char *argv[]){

   printf("\ndbc - version %s%s \n\n", RELEASE, REVISION);

   char *filename = "dummy";
   int id = 0;
   char action = 'x';

   if(argc == 1){
      /* NO ARGS MEAN RUN TESTS */ 
      printf("Test: starting\n");
      char *testfile = "test.db";
      action = 'c';
      struct Connection *conn = Database_open(testfile, action);
      test_setup(conn,id);
      test_1(conn,id);
      test_2(conn,id);
      test_teardown(conn);
      stop_test();
   }
   else if (argc < 3){
      die("USAGE: dbc <dbfile> <action> [action params]");
   }

   filename = argv[1];
   action = argv[2][0];
   char *name = argv[4];
   char *email = argv[5];
   //for (int i = 0; i < argc; i++) {
   //printf("Argc: %d - argv: %s\n", i, argv[i]);
   //}
   if(argc > 3){
      id = atoi(argv[3]);
   }

   if(id >= MAX_ROWS) die("There's not that many records.");
   FILE *file;
   if (!(file = fopen(filename, "r")) && action == 'c') {
      die("File exists && create");
   }
   struct Connection *conn = Database_open(filename, action);

   Process_action(action, name, email, conn, id);

   Database_write(conn);
   Database_close(conn);

   return 0;
}
