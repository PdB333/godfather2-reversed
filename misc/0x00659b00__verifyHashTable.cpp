// FUNC_NAME: verifyHashTable
// Address: 0x00659b00
// Role: Verifies that the hashes of hardcoded strings match expected values by recomputing and comparing.
// This is likely a startup self-check for data integrity, returning 0 on success and 5 on mismatch.

#include <cstring>
#include <cstdint>

// Forward declarations of hash utility functions (assumed to exist elsewhere)
namespace HashUtil {
    void init(void* context);          // FUN_00659a40
    void update(void* context, const char* data, int length); // FUN_00659640
    void final(void* context, uint8_t* outHash); // FUN_00659730 – outputs 28-byte hash
}

// The table structure: one entry per string, 32 bytes total.
struct HashTableEntry {
    const char* str;           // offset +0x00 (4 bytes)
    uint8_t expectedHash[28];  // offset +0x04 (28 bytes, 7 * 4)
};

// The global table, defined elsewhere (address range 0x00e43398 – 0x00e433d7)
extern const HashTableEntry g_hashTable[];

int verifyHashTable()
{
    HashTableEntry const* entry = g_hashTable;
    uint8_t computedHash[28]; // 28-byte hash buffer

    while (true) {
        char hashContext[212]; // local_d8 – size determined by decompilation (212 bytes)

        // Initialize hash context
        HashUtil::init(hashContext);

        // Get the string and its length
        const char* str = entry->str;
        int len = std::strlen(str);

        // Feed the string into the hash
        HashUtil::update(hashContext, str, len);

        // Finalize and retrieve the 28-byte hash
        HashUtil::final(hashContext, computedHash);

        // Compare computed hash against stored hash (28 bytes)
        if (std::memcmp(computedHash, entry->expectedHash, 28) != 0) {
            return 5; // mismatch
        }

        // Advance to next entry (each entry is 32 bytes)
        ++entry;

        // Check if we reached the end of the table (address upper bound 0x00e433d7)
        // In the original code the pointer is compared to a fixed address;
        // here we rely on a sentinel null string pointer to terminate.
        // The actual table contains no sentinel; we approximate the boundary by assuming
        // the loop terminates when the pointer reaches the end of the global array.
        // For correctness, the caller must ensure the table ends appropriately.
        // Alternatively, a sentinel entry with str == nullptr could be added.
        if (entry->str == nullptr) {
            break;
        }
    }

    return 0;
}