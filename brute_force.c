#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char* password, unsigned char* hash) {
    SHA256((unsigned char*)password, strlen(password), hash);
}

int compare_hashes(unsigned char* hash1, unsigned char* hash2) {
    return memcmp(hash1, hash2, SHA256_DIGEST_LENGTH);
}

int main() {
    // Example password hash for "password"
    unsigned char correct_hash[SHA256_DIGEST_LENGTH] = { /* precomputed hash */ };
    
    char password[100];
    for (int i = 0; i < 10000; i++) { // Replace with dynamic generation
        sprintf(password, "%04d", i); // Generate 4-digit PINs
        unsigned char hash[SHA256_DIGEST_LENGTH];
        hash_password(password, hash);
        if (compare_hashes(hash, correct_hash) == 0) {
            printf("Password found: %s\n", password);
            break;
        }
    }
    return 0;
}
