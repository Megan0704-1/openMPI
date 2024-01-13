#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
} Address;

typedef struct Database{
    Address rows[MAX_ROWS];
} Database;

typedef struct Connection {
    FILE *file;
    Database *db;
} Connection;

void die(const char* msg){
    if(errno){
        perror(msg);
    }else{
        printf("ERROR: %s\n", msg);
    }
    exit(1);
}

void printAddress(Address *addr){
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void loadDatabase(Connection *con){
    int rc = fread(con->db, sizeof(Database), 1, con->file);
    if(rc != 1) die("Failed to load database.");
}

Connection *openDatabase(const char *filename, char mode){
    Connection *con = malloc(sizeof(Connection));

    if(!con) die("Memory error");

    con->db = malloc(sizeof(Database));

    if(!con->db) die("Memory error");

    if(mode == 'c'){
        // create and write database
        con->file = fopen(filename, 'w');
    }else{
        // read and exec
        con->file = fopen(filename, 'r+');

        if(con->file) loadDatabase(con);
    }

    if(!con->file) die("Failed to open the file.");
    return con;
}

void closeDatabase(Connection *con){
    if(con){
        if(con->file) fclose(con->file);
        if(con->db) free(con->db);
        free(con);
    }
}

void writeDatabase(Connection *con){
    rewind(con->file);

    int rc = fwrite(con->db, sizeof(Database), 1, con->file);
    if(rc != 1) die("Failed to write database.");
    rc = fflush(con->file);
    if(rc == -1) die("Error flushing database.");
}

void createDatabase(Connection *con){
    for(int i=0; i<MAX_ROWS; i++){
        // make a prototype to initialize it
        Address addr = {.id = i, .set = 0};
        con->db->rows[i] = addr;
    }
}

void setDatabase(Connection *con, int id, const char *name, const char *email){
    Address *addr = &con->db->rows[id];
    if(addr->set) die("Address exist, del first.");
    addr->set = 1;
    char *res = strncpy(addr->name, name, MAX_DATA);

    if(!res) die("Name copy failed.");

    res = strncpy(addr->email, email, MAX_DATA);

    if(!res) die("Email copy failed.");
}

void getDatabase(Connection *con, int id){
    Address *addr = &con->db->rows[id];

    if(addr->set) printAddress(addr);
    else die("ID is not set.");
}

void deleteDatabase(Connection *con, int id){
    Address* addr = {.id=0, .set=0};
    con->db->rows[id] = addr;
}

void listDatabase(Connection *con){
    Database *db = con->db;
    for(int i=0; i<MAX_ROWS; i++){
        Address* cur = &db->rows[i];
        if(cur->set) printAddress(cur);
    }
}

int main(int argc, char* argv[]){
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    Connection* con = openDatabase(filename, action);
    int id=0;

    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("Segmentation fault.");

    switch(action){
        case 'c':
            printf("creating database.\n");
            createDatabase(con);
            writeDatabase(con);
            break;
        case 'g':
            printf("getting address.\n");
            if(argc != 4) die("Input ID number to get address.");
            getDatabase(con, id);
            break;
        case 's':
            printf("setting address.\n");
            if(argc != 6) die("Need id, name, email to set address.");
            setDatabase(con, id, argv[4], argv[5]);
            writeDatabase(con);
            break;
        case 'd':
            printf("deleting address.\n");
            if(argc != 4) die("Input ID number to del address.");
            deleteDatabase(con, id);
            writeDatabase(con);
            break;
        case 'l':
            printf("listing database.\n");
            listDatabase(con);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=delete, l=list");
    }
    closeDatabase(con);

    return 0;
}
