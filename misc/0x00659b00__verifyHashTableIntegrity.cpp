// FUNC_NAME: verifyHashTableIntegrity
// Function at 0x00659b00 checks integrity of embedded string-to-hash mappings.
// Iterates over a table at 0x00e43398, computes 28-byte hash via init/update/finalize,
// compares to stored hash. Returns 0 on success (all match), 5 on failure.

#include <cstdint>

// Forward declarations for helper functions
void hashInit(void* ctx);                     // FUN_00659a40
void hashUpdate(void* ctx, const char* data, int length); // FUN_00659640
void hashFinalize(void* ctx, uint32_t* out);  // FUN_00659730

struct HashTableEntry {
    const char* str;         // +0x00
    uint32_t hash[7];        // +0x04 (28 bytes)
};

// Table at 0x00e43398 (2 entries)
extern HashTableEntry hashTable[2];

int verifyHashTableIntegrity() {
    // 212-byte hash context (size may vary)
    char ctx[212];
    uint32_t computedHash[7]; // 28 bytes

    for (int i = 0; i < 2; ++i) {
        const char* str = hashTable[i].str;
        // Initialize hash context
        hashInit(ctx);
        // Hash the string (length without null terminator)
        int len = 0;
        while (str[len] != '\0') ++len;
        hashUpdate(ctx, str, len);
        // Finalize and get the 28-byte hash
        hashFinalize(ctx, computedHash);

        // Compare computed hash with stored hash
        int cmpResult = 0;
        for (int j = 0; j < 7; ++j) {
            if (computedHash[j] != hashTable[i].hash[j]) {
                if (computedHash[j] > hashTable[i].hash[j]) {
                    cmpResult = 1;
                } else {
                    cmpResult = -1;
                }
                break;
            }
        }
        if (cmpResult != 0) {
            return 5; // hash mismatch
        }
    }
    return 0; // all hashes match
}