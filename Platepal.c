#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Platepal.h"

void addNewRecipes(MYSQL *conn) {
    // adding a new recipe
    char query[MAX_QUERY_LEN];
    char buffer[MAX_STRING_LEN];

    printf("Do you want to add a new recipe to database? (y/n): ");
    fgets(buffer, MAX_STRING_LEN, stdin);
    if (tolower(buffer[0]) == 'y') {
        // Gather recipe information
        char recipeId[12];
        char recipeName[MAX_STRING_LEN];
        char recipeIngredientsAmount[MAX_STRING_LEN];
        char recipeIngredients[MAX_STRING_LEN];
        char recipeInstructions[MAX_STRING_LEN];

        printf("Enter recipe name: ");
        fgets(recipeName, MAX_STRING_LEN, stdin);
        recipeName[strcspn(recipeName, "\n")] = '\0';

        printf("Enter recipe instructions: ");
        fgets(recipeInstructions, MAX_STRING_LEN, stdin);
        recipeInstructions[strcspn(recipeInstructions, "\n")] = '\0';

        printf("Enter the first ingredient amount: ");
        fgets(recipeIngredientsAmount, MAX_STRING_LEN, stdin);
        recipeIngredientsAmount[strcspn(recipeIngredientsAmount, "\n")] = '\0';

        printf("Enter the first ingredient: ");
        fgets(recipeIngredients, MAX_STRING_LEN, stdin);
        recipeIngredients[strcspn(recipeIngredients, "\n")] = '\0';

        // Generate recipe id
        execute_query(conn, "SELECT MAX(recipeId) FROM RecipesTable");
        MYSQL_RES *result = mysql_use_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);
        int max_id = row[0] != NULL ? atoi(row[0]) : 0;
        snprintf(recipeId, sizeof(recipeId), "%d", max_id + 1);
        mysql_free_result(result);

        // Insert first ingredient
        snprintf(query, MAX_QUERY_LEN, "INSERT INTO RecipesTable (recipeId, recipeName, recipeIngredientsAmount, recipeIngredients, recipeInstructions) VALUES ('%s', '%s', '%s', '%s', '%s')", recipeId, recipeName, recipeIngredientsAmount, recipeIngredients, recipeInstructions);
        execute_query(conn, query);

        bool moreIngredients = true;
        while (moreIngredients) {
            printf("Do you have more ingredients to add? (y/n): ");
            fgets(buffer, MAX_STRING_LEN, stdin);
            if (tolower(buffer[0]) == 'y') {
                printf("Enter the next ingredient amount: ");
                fgets(recipeIngredientsAmount, MAX_STRING_LEN, stdin);
                recipeIngredientsAmount[strcspn(recipeIngredientsAmount, "\n")] = '\0';

                printf("Enter the next ingredient: ");
                fgets(recipeIngredients, MAX_STRING_LEN, stdin);
                recipeIngredients[strcspn(recipeIngredients, "\n")] = '\0';

                // Insert additional ingredient
                snprintf(query, MAX_QUERY_LEN, "INSERT INTO RecipesTable (recipeId, recipeName, recipeIngredientsAmount, recipeIngredients, recipeInstructions) VALUES ('%s', '%s', '%s', '%s', '%s')", recipeId, recipeName, recipeIngredientsAmount, recipeIngredients, recipeInstructions);
                execute_query(conn, query);
            } else {
                moreIngredients = false;
            }
        }
    }
}

void recipeSuggestion(MYSQL *conn) {
    char buffer[MAX_STRING_LEN];
    char query[MAX_QUERY_LEN];
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    // Get a list of all recipe IDs
    execute_query(conn, "SELECT DISTINCT recipeId FROM RecipesTable");
    result = mysql_use_result(conn);
    int numIds = 0;
    while ((row = mysql_fetch_row(result))) {
        numIds++;
    }
    mysql_free_result(result);
    if (numIds == 0) {
        printf("No recipes found.\n");
        return;
    }

    int *recipeIds = (int *) malloc(numIds * sizeof(int));
    int i = 0;
    execute_query(conn, "SELECT DISTINCT recipeId FROM RecipesTable");
    result = mysql_use_result(conn);
    while ((row = mysql_fetch_row(result))) {
        recipeIds[i++] = atoi(row[0]);
    }
    mysql_free_result(result);
    
    while (true) {
        printf("Do you want a recipe suggestion? (y/n): ");
        fgets(buffer, MAX_STRING_LEN, stdin);
        if (tolower(buffer[0]) != 'y') {
            break;
        }
        // Choose a random recipe ID from the list
        int randIdx = rand() % numIds;
        int recipeId = recipeIds[randIdx];
        
        // Print all rows with the chosen recipe ID
        snprintf(query, MAX_QUERY_LEN, "SELECT * FROM RecipesTable WHERE recipeId = %d", recipeId);
        execute_query(conn, query);
        result = mysql_use_result(conn);
        char *tempRecipeInstructions = NULL;
        while ((row = mysql_fetch_row(result))) {
            printf("%s %s %s \n", row[1], row[2], row[3]); 
            if (row[4] != NULL) {
                tempRecipeInstructions = row[4];
            }
        }
        printf("\n");
        printf("%s\n", tempRecipeInstructions);

        mysql_free_result(result);
    }
    free(recipeIds);
}

void execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void printRecipes(MYSQL *conn) {
    // Print all recipes
    execute_query(conn, "SELECT * FROM RecipesTable");
    MYSQL_RES *result = mysql_use_result(conn);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4]);
    }
    mysql_free_result(result);
}
