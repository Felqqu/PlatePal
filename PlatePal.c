#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Recipes.h"

#define MAX_INGREDIENTS 10
#define MAX_RECIPES 10


void printShoppingList(int *shoppingList, int numIngredients) {
    for (int i = 0; i < NUM_INGREDIENTS; i++) {
        if (shoppingList[i] > 0) {
            printf("%s: %d\n", INGREDIENT_NAMES[i], shoppingList[i]);
        }
    }
    printf("Total number of ingredients: %d\n", numIngredients);
}

int main() {
    int shoppingList[NUM_INGREDIENTS] = {0};
    int numIngredients = 0;
    int recipeChoice = 0;
    char choice;
    int suggestedRecipes[NUM_RECIPES] = {0};  // array to keep track of suggested recipes
    int numSuggested = 0;  // number of suggested recipes so far

    printf("Welcome to PlatePal!\n");

    while (1) {
        printf("Would you like a recipe suggestion? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n') {
            printf("Okay, have a good day! Here are the needed ingredients:\n");
            printf("Ingredients:\n");
            for (int i = 0; i < NUM_INGREDIENTS; i++) {
                if (RECIPES[recipeChoice].ingredients[i] > 0) {
                    printf("%s: %d\n", INGREDIENT_NAMES[i], RECIPES[recipeChoice].ingredients[i]);
                    shoppingList[i] += RECIPES[recipeChoice].ingredients[i];
                    numIngredients += RECIPES[recipeChoice].ingredients[i];
                }
            }
            break;

            // Prompt user to indicate which ingredients they already have
            printf("Do you have any of these ingredients? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y') {
                for (int i = 0; i < NUM_INGREDIENTS; i++) {
                    if (RECIPES[recipeChoice].ingredients[i] > 0) {
                        printf("%s: ", INGREDIENT_NAMES[i]);
                        int haveIngredient = 0;
                        scanf("%d", &haveIngredient);
                        if (haveIngredient > 0) {
                            shoppingList[i] -= haveIngredient;
                            numIngredients -= haveIngredient;
                        }
                    }
                }
            }

            break;
        } else if (choice == 'y') {
            // Generate a new random number until it corresponds to an unsuggested recipe
            do {
                recipeChoice = rand() % NUM_RECIPES;
            } while (suggestedRecipes[recipeChoice] == 1);

            suggestedRecipes[recipeChoice] = 1;
            numSuggested++;

            printf("We suggest trying: %s\n", RECIPES[recipeChoice].name);
            printf("Ingredients:\n");
            for (int i = 0; i < NUM_INGREDIENTS; i++) {
                if (RECIPES[recipeChoice].ingredients[i] > 0) {
                    printf("%s: %d\n", INGREDIENT_NAMES[i], RECIPES[recipeChoice].ingredients[i]);
                    shoppingList[i] += RECIPES[recipeChoice].ingredients[i];
                    numIngredients += RECIPES[recipeChoice].ingredients[i];
                }
            }

            // Prompt user to indicate which ingredients they already have
            printf("Do you have any of these ingredients? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y') {
                for (int i = 0; i < NUM_INGREDIENTS; i++) {
                    if (RECIPES[recipeChoice].ingredients[i] > 0) {
                        printf("%s: ", INGREDIENT_NAMES[i]);
                        int haveIngredient = 0;
                        scanf("%d", &haveIngredient);
                        if (haveIngredient > 0) {
                            shoppingList[i] -= haveIngredient;
                            numIngredients -= haveIngredient;
                        }
                    }
                }
            }

            printf("Your updated shopping list:\n");
            printShoppingList(shoppingList, numIngredients);

            // If all recipes have been suggested, reset the suggestedRecipes array
            if (numSuggested == NUM_RECIPES) {
                for (int i = 0; i < NUM_RECIPES; i++) {
                    suggestedRecipes[i] = 0;
                }
                numSuggested = 0;
            }
        } else {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
    }

    return 0;
}

