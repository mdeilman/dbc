/* forward declarations test and logging*/
void test_setup();
void test_teardown();
void test_1();
void test_2();

void test_setup(struct Connection *conn, int id){
    Process_action('c',"dummy","dummy",conn,id);
}

void test_teardown(struct Connection *conn){
        Database_write(conn);
        Database_close(conn);
}

void test_1(struct Connection *conn, int id){
    log_test("1");
    log_test("adding Mario, a@b.c");
    Process_action('s',"Mario","a@b.c",conn,id++);
    log_test("adding Hans, b@b.c");
    Process_action('s',"Hans","b@b.c",conn,id++);
    log_test("adding Ulla, c@b.c");
    Process_action('s',"Ulla","c@b.c",conn,id++);
    log_test("adding Maria, d@b.c");
    Process_action('s',"Maria","d@b.c",conn,id++);
    log_test("adding Fritz, e@b.c");
    Process_action('s',"Fritz","e@b.c",conn,id++);
    log_test("listing database");
    Process_action('l',"dummy","dummy",conn,id);
}

void test_2(struct Connection *conn, int id){
    log_test("2");
    log_test("adding Zed, zed@zedshaw.com");
    Process_action('s',"Zed","zed@zedshaw.com",conn,5);
    log_test("listing database");
    Process_action('l',"dummy","dummy",conn,id);
}
