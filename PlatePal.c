#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Recipes.h"

#define MAX_INGREDIENTS 10
#define MAX_RECIPES 10


void print_shopping_list(int *shopping_list, int num_ingredients) {
    for (int i = 0; i < NUM_INGREDIENTS; i++) {
        if (shopping_list[i] > 0) {
            printf("%s: %d\n", INGREDIENT_NAMES[i], shopping_list[i]);
        }
    }
    printf("Total number of ingredients: %d\n", num_ingredients);
}

int main() {
    int shopping_list[NUM_INGREDIENTS] = {0};
    int num_ingredients = 0;
    int recipe_choice = 0;
    char choice;
    int suggested_recipes[NUM_RECIPES] = {0};  // array to keep track of suggested recipes
    int num_suggested = 0;  // number of suggested recipes so far

    printf("Welcome to PlatePal!\n");

    while (1) {
        printf("Would you like a recipe suggestion? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n') {
            printf("Okay, have a good day! Here are the needed ingredients:\n");
            printf("Ingredients:\n");
            for (int i = 0; i < NUM_INGREDIENTS; i++) {
                if (RECIPES[recipe_choice].ingredients[i] > 0) {
                    printf("%s: %d\n", INGREDIENT_NAMES[i], RECIPES[recipe_choice].ingredients[i]);
                    shopping_list[i] += RECIPES[recipe_choice].ingredients[i];
                    num_ingredients += RECIPES[recipe_choice].ingredients[i];
                }
            }
            break;

            // Prompt user to indicate which ingredients they already have
            printf("Do you have any of these ingredients? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y') {
                for (int i = 0; i < NUM_INGREDIENTS; i++) {
                    if (RECIPES[recipe_choice].ingredients[i] > 0) {
                        printf("%s: ", INGREDIENT_NAMES[i]);
                        int have_ingredient = 0;
                        scanf("%d", &have_ingredient);
                        if (have_ingredient > 0) {
                            shopping_list[i] -= have_ingredient;
                            num_ingredients -= have_ingredient;
                        }
                    }
                }
            }

            break;
        } else if (choice == 'y') {
            // Generate a new random number until it corresponds to an unsuggested recipe
            do {
                recipe_choice = rand() % NUM_RECIPES;
            } while (suggested_recipes[recipe_choice] == 1);

            suggested_recipes[recipe_choice] = 1;
            num_suggested++;

            printf("We suggest trying: %s\n", RECIPES[recipe_choice].name);
            printf("Ingredients:\n");
            for (int i = 0; i < NUM_INGREDIENTS; i++) {
                if (RECIPES[recipe_choice].ingredients[i] > 0) {
                    printf("%s: %d\n", INGREDIENT_NAMES[i], RECIPES[recipe_choice].ingredients[i]);
                    shopping_list[i] += RECIPES[recipe_choice].ingredients[i];
                    num_ingredients += RECIPES[recipe_choice].ingredients[i];
                }
            }

            // Prompt user to indicate which ingredients they already have
            printf("Do you have any of these ingredients? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y') {
                for (int i = 0; i < NUM_INGREDIENTS; i++) {
                    if (RECIPES[recipe_choice].ingredients[i] > 0) {
                        printf("%s: ", INGREDIENT_NAMES[i]);
                        int have_ingredient = 0;
                        scanf("%d", &have_ingredient);
                        if (have_ingredient > 0) {
                            shopping_list[i] -= have_ingredient;
                            num_ingredients -= have_ingredient;
                        }
                    }
                }
            }

            printf("Your updated shopping list:\n");
            print_shopping_list(shopping_list, num_ingredients);

            // If all recipes have been suggested, reset the suggested_recipes array
            if (num_suggested == NUM_RECIPES) {
                for (int i = 0; i < NUM_RECIPES; i++) {
                    suggested_recipes[i] = 0;
                }
                num_suggested = 0;
            }
        } else {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
    }

    return 0;
}

