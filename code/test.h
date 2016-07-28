#ifndef TEST_H_
#define TEST_H_

#include<stdlib.h>
#include<time.h>

/* forward declarations test and logging*/
void run_test();
void test_setup();
void test_teardown();
void test_1();
void test_2();

#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )

char* name_arr[] = {"Peter", "Paul", "Mary", "Pipi", "Kaka", " ", "Mario", "Zed", "Paula"};
char* email_arr[] = {"Peter@yahho.de", "Paul@gmx.de", "Mary@yahoo.de", "Pipi@microsoft.com", "Kaka@apple.com", " ", "Mario@nds.com", "Zed@empire.co.uk.", "Paula@goolge.com"};


void test_setup(struct Connection *conn, int id){
    Process_action('c',"dummy","dummy",conn,id);
}

void test_teardown(struct Connection *conn){
        Database_write(conn);
        Database_close(conn);
}

void test_run(struct Connection *conn, int id, int runs){
    int rnd_index=0;
    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));    

    log_test("Test 1");
    
    for (int i = 0; i < runs; i++){
        rnd_index = rand() % ARR_SIZE(name_arr) ;
        printf ("Rnd nb: %d \n", rnd_index );
        printf ("Now I choose %s \n", name_arr[rnd_index] );
        printf ("Now I choose %s \n", email_arr[rnd_index] );
        // ToDo: Tests if name array and semail array have the same length
        //log_test("adding: %s - %s",name_arr[rnd_index],email_arr[rnd_index]);
        log_test("adding stuff");
        Process_action('s',name_arr[rnd_index],email_arr[rnd_index],conn,id++);
    }
}

void run_test(){
    printf("Test: starting\n");
    char *testfile = "test.db";
    char action = 'c';
    char id = 0;
    int nb_runs = 100;
    struct Connection *conn = Database_open(testfile, action);
    test_setup(conn,id);
    test_run(conn,id,nb_runs);
    test_teardown(conn);
    stop_test();
    printf("Test: finished\n");
}

#endif // TEST_H_
