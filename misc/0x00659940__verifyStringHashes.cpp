// FUNC_NAME: verifyStringHashes
// Function at 0x00659940: Verifies a list of strings against precomputed SHA-256 hashes stored in a table.
// Returns 0 if all hashes match, 5 if any mismatch.
// Table at PTR_DAT_00e43318: each entry is 9 pointers (36 bytes): [stringPtr, hash0, hash1, hash2, hash3, hash4, hash5, hash6, hash7]
// Hash is 32 bytes (8 dwords). The function computes SHA-256 of each string and compares.

#include <cstdint>

// Forward declarations of helper functions (likely SHA-256 context operations)
void hashInit(uint8_t* context);          // FUN_006595c0
void hashUpdate(uint8_t* context, const char* data, int length); // FUN_00659640
void hashFinal(uint8_t* context, uint8_t* digest); // FUN_00659730

int verifyStringHashes()
{
    // Table of entries: each entry is 9 pointers (36 bytes)
    // The table is stored at PTR_DAT_00e43318, ends at 0xe4335f (inclusive? Actually loop condition: ppuVar9 <= 0xe4335f)
    // We'll iterate through it.
    uint8_t** tableEntry = reinterpret_cast<uint8_t**>(0x00e43318);
    uint8_t* endPtr = reinterpret_cast<uint8_t*>(0x00e43360); // one past last valid entry

    while (tableEntry < reinterpret_cast<uint8_t**>(endPtr))
    {
        // Allocate context and digest on stack (244 bytes total, context at +0x20)
        uint8_t buffer[244]; // local_f8
        uint8_t* context = buffer + 0x20;
        uint8_t* digest = buffer;

        // Initialize hash context
        hashInit(context);

        // Get string pointer from table
        const char* str = reinterpret_cast<const char*>(tableEntry[0]);
        int strLen = 0;
        while (str[strLen] != '\0') strLen++;

        // Update hash with string
        hashUpdate(context, str, strLen);

        // Finalize hash into digest
        hashFinal(context, digest);

        // Compare digest with stored hash (next 8 pointers = 32 bytes)
        uint8_t* storedHash = reinterpret_cast<uint8_t*>(&tableEntry[1]); // 8 dwords = 32 bytes
        int cmpResult = 0;
        // Unrolled comparison (original code does 32-byte compare in 4-byte chunks)
        for (int i = 0; i < 8; i++)
        {
            uint32_t computed = reinterpret_cast<uint32_t*>(digest)[i];
            uint32_t stored = reinterpret_cast<uint32_t*>(storedHash)[i];
            if (computed != stored)
            {
                // Determine sign for return value (original returns 5 on mismatch, not -1)
                // The original code sets iVar5 = 1 if computed > stored, -1 if computed < stored, then returns 5 if iVar5 != 0.
                // But it always returns 5 on mismatch regardless of sign? Actually it returns 5 if iVar5 != 0.
                // So any mismatch returns 5.
                return 5;
            }
        }

        // Move to next entry (9 pointers forward)
        tableEntry += 9;
    }

    // All entries matched
    return 0;
}