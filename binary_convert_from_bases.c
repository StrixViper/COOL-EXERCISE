#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to convert binary to decimal
long long binaryToDecimal(char* binary) {
    long long decimal = 0;
    int length = strlen(binary);

    for (int i = 0; i < length; i++) {
        if (binary[length - i - 1] == '1') {
            decimal += (1LL << i);  // Equivalent to 2^i
        }
    }
    return decimal;
}

// Function to convert decimal to binary
void decimalToBinary(long long decimal) {
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    char binary[64];
    int index = 0;

    while (decimal > 0) {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }

    // Reverse the binary array
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", binary[i]);
    }
    printf("\n");
}

// Function to convert octal to decimal
long long octalToDecimal(char* octal) {
    long long decimal = 0;
    int length = strlen(octal);

    for (int i = 0; i < length; i++) {
        decimal = decimal * 8 + (octal[i] - '0');
    }
    return decimal;
}

// Function to convert decimal to octal
void decimalToOctal(long long decimal) {
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    char octal[64];
    int index = 0;

    while (decimal > 0) {
        octal[index++] = (decimal % 8) + '0';
        decimal /= 8;
    }

    // Reverse the octal array
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", octal[i]);
    }
    printf("\n");
}

// Function to convert hexadecimal to decimal
long long hexadecimalToDecimal(char* hex) {
    long long decimal = 0;
    int length = strlen(hex);

    for (int i = 0; i < length; i++) {
        char digit = hex[i];
        if (digit >= '0' && digit <= '9') {
            decimal = decimal * 16 + (digit - '0');
        } else if (digit >= 'A' && digit <= 'F') {
            decimal = decimal * 16 + (digit - 'A' + 10);
        } else if (digit >= 'a' && digit <= 'f') {
            decimal = decimal * 16 + (digit - 'a' + 10);
        }
    }
    return decimal;
}

// Function to convert decimal to hexadecimal
void decimalToHexadecimal(long long decimal) {
    if (decimal == 0) {
        printf("0\n");
        return;
    }
    char hex[64];
    int index = 0;

    while (decimal > 0) {
        int remainder = decimal % 16;
        if (remainder < 10) {
            hex[index++] = remainder + '0';
        } else {
            hex[index++] = remainder - 10 + 'A';
        }
        decimal /= 16;
    }

    // Reverse the hex array
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", hex[i]);
    }
    printf("\n");
}

// Function to choose conversion type and perform the conversion
void convert(char* input, int fromBase, int toBase) {
    long long decimal = 0;

    // Convert from the given base to decimal
    if (fromBase == 2) {
        decimal = binaryToDecimal(input);
    } else if (fromBase == 8) {
        decimal = octalToDecimal(input);
    } else if (fromBase == 10) {
        decimal = atoll(input);  // Convert string to long long
    } else if (fromBase == 16) {
        decimal = hexadecimalToDecimal(input);
    }

    // Convert from decimal to the desired base
    printf("Result: ");
    if (toBase == 2) {
        decimalToBinary(decimal);
    } else if (toBase == 8) {
        decimalToOctal(decimal);
    } else if (toBase == 10) {
        printf("%lld\n", decimal);
    } else if (toBase == 16) {
        decimalToHexadecimal(decimal);
    }
}

int main() {
    char input[64];
    int fromBase, toBase;

    printf("Enter the number: ");
    scanf("%s", input);

    printf("Enter the base you're converting from (2, 8, 10, 16): ");
    scanf("%d", &fromBase);

    printf("Enter the base you're converting to (2, 8, 10, 16): ");
    scanf("%d", &toBase);

    // Perform the conversion
    convert(input, fromBase, toBase);

    return 0;
}
