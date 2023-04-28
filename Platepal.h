#ifndef PLATEPAL_H
#define PLATEPAL_H

#include <mysql/mysql.h>

#define MAX_QUERY_LEN 5000
#define MAX_STRING_LEN 1024

extern MYSQL *conn;

void recipeSuggestion(MYSQL *conn);
void addNewRecipes(MYSQL *conn);
void printRecipes(MYSQL *conn);
//Function prototype for compiler
void execute_query(MYSQL *conn, const char *query);

#endif /* PLATEPAL_H */