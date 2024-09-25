#include <stdio.h>
#include <string.h>

// Enum to define the type of the variable
typedef enum {
    VAR_TYPE_INT,
    VAR_TYPE_FLOAT,
    VAR_TYPE_STRING
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

// Function to set an integer value
void setInt(Var *var, int value) {
    var->value.intValue = value;
    var->type = VAR_TYPE_INT;
}

// Function to set a float value
void setFloat(Var *var, float value) {
    var->value.floatValue = value;
    var->type = VAR_TYPE_FLOAT;
}

// Function to set a string value
void setString(Var *var, const char *value) {
    strncpy(var->value.strValue, value, sizeof(var->value.strValue) - 1);
    var->value.strValue[sizeof(var->value.strValue) - 1] = '\0'; // Ensure null-termination
    var->type = VAR_TYPE_STRING;
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

    setInt(&myVar, 10);
    printVar(&myVar);

    setFloat(&myVar, 3.14f);
    printVar(&myVar);

    setString(&myVar, "Hello, World!");
    printVar(&myVar);

    return 0;
}
