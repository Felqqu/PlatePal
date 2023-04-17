#include "Recipes.h"

const Recipe RECIPES[NUM_RECIPES] = {
    {"Caprese Salad", {0, 0, 0, 1, 1, 0, 0, 0, 1, 3}},
    {"Roasted Chicken", {0, 0, 1, 1, 0, 1, 0, 0, 0, 0}},
    {"Pesto Pasta", {0, 0, 0, 1, 1, 0, 0, 0, 1, 3}},
    {"Grilled Fish Tacos", {0, 1, 1, 0, 1, 0, 0, 0, 1, 2}},
    {"Vegetable Stir Fry", {0, 0, 1, 1, 1, 0, 1, 0, 0, 0}},
    {"Chicken Caesar Salad", {0, 0, 0, 1, 1, 1, 0, 0, 1, 3}},
    {"BBQ Ribs", {1, 0, 0, 1, 0, 0, 1, 0, 0, 0}},
    {"Beef Tacos", {1, 0, 0, 1, 1, 0, 0, 0, 1, 2}},
    {"Fruit Salad", {0, 0, 0, 0, 1, 0, 0, 0, 0, 3}}
};

const char *INGREDIENT_NAMES[NUM_INGREDIENTS] = {
    "Ground Beef",
    "Tuna",
    "Bell Pepper",
    "Onion",
    "Tomato",
    "Chicken Thighs",
    "Soy Sauce",
    "Pesto Sauce",
    "Cheese",
    "Pasta"
};