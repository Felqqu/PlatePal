#ifndef RECIPES_H
#define RECIPES_H

#define NUM_INGREDIENTS 10
#define MAX_NAME_LENGTH 30
#define NUM_RECIPES 10

typedef struct Recipe {
    char name[MAX_NAME_LENGTH];
    int ingredients[NUM_INGREDIENTS];
} Recipe;

extern const Recipe RECIPES[NUM_RECIPES];
extern const char *INGREDIENT_NAMES[NUM_INGREDIENTS];

#endif
