/* forward declarations test and logging*/
void die();
void log_msg();
void log_test();
void stop_test();
/* end forward declarations test and logging*/

/* forward declarations db */
void Address_print();
void Database_load();
void Database_close();
void Database_write();
void Database_create();
void Database_set();
void Database_get();
void Database_delete();
void Database_list();
//void Process_action();
/* end forward declarations db */

/* macros */
#define UNUSED(x) (void)(x)
#define NOTUSED(...) (void)(__VA_ARGS__)
/* Note: The UNUSED macro won't work for arguments which contain parenthesis, so if you have an argument like float (*coords)[3] you can't do, float UNUSED((*coords)[3]) or float (*UNUSED(coords))[3], This is the only downside to the UNUSED macro I found so far, in these cases I fall back to (void)coords;*/
/* end macros */

/* --- data structures ---*/

/* Todo: Keep some data about the database */
struct db_info {
    int db_size;
    int db_curr_pos;
};

struct Address {
    char strt;
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
    char ends;
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

struct Connection *Database_open(const char *filename, char mode){
    /* reserve memory */
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");
    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error");
    /* connect file to database */
    if(mode == 'c') {
        /* ToDo: database if exists get overwritten*/
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if(conn->file) {
            Database_load(conn);
        }
    }
    if(!conn->file) die("Failed to open the file");
    return conn;
}
/* --- data structures ----*/

/* end forward declarations process_action */
void Process_action(char action, char *name, char *email, struct Connection *conn, int id);
/* end forward declarations process_action */


void die(const char *message){
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

void log_msg(const char *message){
    #ifdef LOG
    printf("Log: %s\n", message);
    #else
    UNUSED(message);
    #endif
}

void log_test(const char *message){
    #ifdef TEST
    printf("Test: %s\n", message);
    #else
    UNUSED(message);
    #endif
}

void stop_test(){
    puts("Test: finished");
    puts("Bailing out ...");
    exit(1);
}

void Address_print(struct Address *addr){
    printf("%d \t%s \t%s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn){
    /* printf("Database_load: Size of struct Database %I64u\n", sizeof(struct Database)); */
    printf("Database_load: Size of struct Database %lu\n", sizeof(struct Database));
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.");
    log_msg("database load");
}

void Database_close(struct Connection *conn){
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
    log_msg("database close");
}

void Database_write(struct Connection *conn){
    rewind(conn->file);
    /*printf("Database_write: Size of struct Database %I64u\n", sizeof(struct Database));*/
    printf("Database_write: Size of struct Database %lu\n", sizeof(struct Database));

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.");
    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
    log_msg("database written");
}

void Database_create(struct Connection *conn){

    for(int i = 0; i < MAX_ROWS; i++) {
        /* make a prototype to initialize it */
        struct Address addr = {.id = i, .set = 0};
        /* then just assign it */
        conn->db->rows[i] = addr;
    }
    log_msg("database created");
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email){
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");
    addr->set = 1;
    addr->strt = '>';
    addr->ends = '<';
    /* WARNING: bug, read the "How To Break It" and fix this */
    char *res = strncpy(addr->name, name, MAX_DATA);
    /* demonstrate the strncpy bug */
    if(!res) die("Name copy failed");
    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");
    log_msg("database set");
}

void Database_get(struct Connection *conn, int id){
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
    log_msg("database get");
}

void Database_delete(struct Connection *conn, int id){
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
    log_msg("database delete");
}

void Database_list(struct Connection *conn){
    struct Database *db = conn->db;
    printf("ID \tname \tmail\n");
    printf("---------------------\n");
    for(int i = 0; i < 10; i++) {
        /*struct Address *cur = &db->rows[i];
        if(cur->set) {
            Address_print(cur);
        }*/
        Address_print(&db->rows[i]);
    }
    log_msg("database list");
}

void Process_action(char action, char *name, char *email, struct Connection *conn, int id){
    switch(action) {
        case 'c':
            Database_create(conn);
            //Database_write(conn);
            break;
        case 'g':
            /*if(argc != 4) die("Need an id to get");*/
            Database_get(conn, id);
            break;
        case 's':
            /* if(argc != 6) die("Need id, name, email to set");*/
            /* Database_set(conn, id, argv[4], argv[5]);*/
            Database_set(conn, id, name, email);
            //Database_write(conn);
            break;
        case 'd':
            /*if(argc != 4) die("Need id to delete");*/
            Database_delete(conn, id);
            //Database_write(conn);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }
}
