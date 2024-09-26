#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Enum to define the type of the variable
typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_FLOAT,
    VAR_TYPE_STRING,
    VAR_TYPE_UNKNOWN
} VarType;

// Union to hold different types of values
typedef union {
    int intValue;
    float floatValue;
    char strValue[50];
} VarValue;

// Struct to represent a variable that can hold any type
typedef struct {
    VarValue value;
    VarType type;
} Var;

// Function to determine the variable type from a string
VarType determineType(const char *value) {
    char *endptr;

    // Check if it is an integer
    long intValue = strtol(value, &endptr, 10);
    if (*endptr == '\0') {
        return VAR_TYPE_INT;
    }

    // Check if it is a float
    float floatValue = strtof(value, &endptr);
    if (*endptr == '\0') {
        return VAR_TYPE_FLOAT;
    }

    // Otherwise, it is a string
    return VAR_TYPE_STRING;
}

// Function to set a value based on the input string
void setValue(Var *var, const char *value) {
    var->type = determineType(value);

    switch (var->type) {
        case VAR_TYPE_INT:
            var->value.intValue = strtol(value, NULL, 10);
            break;
        case VAR_TYPE_FLOAT:
            var->value.floatValue = strtof(value, NULL);
            break;
        case VAR_TYPE_STRING:
            strncpy(var->value.strValue, value, sizeof(var->value.strValue) - 1);
            var->value.strValue[sizeof(var->value.strValue) - 1] = '\0'; // Ensure null-termination
            break;
        default:
            // Handle unknown type case if necessary
            break;
    }
}

// Function to print the variable based on its type
void printVar(const Var *var) {
    switch (var->type) {
        case VAR_TYPE_INT:
            printf("Integer: %d\n", var->value.intValue);
            break;
        case VAR_TYPE_FLOAT:
            printf("Float: %.2f\n", var->value.floatValue);
            break;
        case VAR_TYPE_STRING:
            printf("String: %s\n", var->value.strValue);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

// Main function to demonstrate the Var functionality
int main() {
    Var myVar;

    setValue(&myVar, "10");
    printVar(&myVar);

    setValue(&myVar, "3.14");
    printVar(&myVar);

    setValue(&myVar, "Hello, World!");
    printVar(&myVar);

    return 0;
}
