#ifndef DBC_H_
#define DBC_H_

/*
  FIXME: There is quite some code in this header which has to be put into *.c files
*/

/* Sorry I finally gave up on cl on Windows, no chance how to handle this consistent between compilers
   and platforms) this is only for the two printf statements in Database_load and Database_write */
#ifdef WIN32
#pragma warning( disable : 4477 )
#endif

/* forward declarations */
struct Connection *Database_open(const char *filename, char mode);
void die(const char *message);
void log_msg(const char *message);
void log_test(const char *message);
void stop_test();
void Address_print(struct Address *addr);
void Database_load(struct Connection *conn);
void Database_close(struct Connection *conn);
void Database_write(struct Connection *conn);
void Database_create(struct Connection *conn);
void Database_set(struct Connection *conn, int id, const char *name, const char *email);
void Database_get(struct Connection *conn, int id);
void Database_delete(struct Connection *conn, int id);
void Database_list(struct Connection *conn);
void Process_action(char action, char *name, char *email, struct Connection *conn, int id);
/* end forward declarations */

#define MAX_DATA 32

/* TODO make the size dynamically allocatable */
#define MAX_ROWS 10000

#define RELEASE "0.1"
#define REVISION ".2"

// #define MYDEBUG 1
// #define LOG 1
#define TEST 1

/* macros */
#define UNUSED(x) (void)(x)
#define NOTUSED(...) (void)(__VA_ARGS__)
/* Note: The UNUSED macro won't work for arguments which contain parenthesis, so if you have an argument like float (*coords)[3] you can't do, float UNUSED((*coords)[3]) or float (*UNUSED(coords))[3], This is the only downside to the UNUSED macro I found so far, in these cases I fall back to (void)coords;*/
/* end macros */

/* --- data structures ---*/

/* FIXME: Keep meta data about the database */

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
    /* FIXME: Database if exists gets overwritten - handling */
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
}

void Address_print(struct Address *addr){
  printf("%d \t%s \t%s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn){
  /*printf("Database_load: Size of struct Database %d [KiloBytes]\n", (sizeof(struct Database))/1024);*/
  printf("Database_load: Size of struct Database %llu [KiloBytes]\n", (sizeof(struct Database))/1024);
  size_t rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
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
  /*
    printf("Database_write: Size of struct Adress %d [Bytes]\n", (sizeof(struct Address)));
    printf("Database_write: Size of struct Database %d [KiloBytes]\n", (sizeof(struct Database))/1024);
  */
  printf("Database_write: Size of struct Adress %llu [Bytes]\n", (sizeof(struct Address)));
  printf("Database_write: Size of struct Database %llu [KiloBytes]\n", (sizeof(struct Database))/1024);
  size_t rc1 = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if(rc1 != 1) die("Failed to write database.");
  size_t rc2 = fflush(conn->file);
  if(rc2 != 0) die("Cannot flush database.");
  log_msg("database written");
}

void Database_create(struct Connection *conn){
  /* 
   *  ToDo: DMC complains about - dmc dbc.c - need fix
   *  struct Address addr = {.id = i, .set = zero};
   *  dbc.h(169) : Error: constant initializer expected
   */
  int zero = 0;
  for(int i = 0; i < MAX_ROWS; i++) {
    /* make a prototype to initialize it */
    struct Address addr = {.id = i, .set = zero};
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
  printf("--> Only printing first 20 elements <--\n");
  printf("ID \tname \tmail\n");
  printf("---------------------\n");
  /* FIXME: List only 10 elements, find out how big the database is */
  for(int i = 0; i < 20; i++) {
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

#endif // DBC_H_
