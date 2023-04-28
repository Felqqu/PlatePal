
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Platepal.h"

int main() {
    
    const char *server = "localhost";
    const char *user = "admin_user";
    const char *password = "PlatePalPass";
    const char *database = "Recipes";
    
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    recipeSuggestion(conn);

    addNewRecipes(conn);
    
    mysql_close(conn);
    
    return 0;
}

