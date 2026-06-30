// FUNC_NAME: StringHashTable::containsString
// Address: 0x00698a40
// Role: Checks if a string (after normalization and possible tokenization) is already registered in the hash table.
// Returns 1 if the string is not found (i.e., can be added), 0 if already present.

#include <cstdint>

// Forward declarations of external functions (EA EARS engine)
extern void normalizeString(char* str);                        // FUN_004d3bc0
extern int  parseTokens(const char* str, int* tokenList, int* tokenCount); // FUN_004dd9e0 (approximate)
extern uint32_t computeStringHash(const char* str, int len);  // FUN_004db320

// Internal structure: each entry in the hash table (0x141 bytes)
struct HashEntry {
    uint32_t hash;      // +0x00: hash code of the string
    // rest of 0x141 - 4 = 317 bytes of unknown data
    uint8_t data[0x141 - 4];
};

// Structure pointed to by this+0x14 (provides table metadata)
struct TableInfo {
    uint8_t unknown[4]; // +0x00
    uint16_t count;     // +0x04: number of entries currently in table
};

// Main class: StringHashTable
class StringHashTable {
public:
    // Member offsets (deduced from decompilation)
    // +0x00: vtable? (not used here)
    // +0x04: m_pTable (pointer to array of HashEntry)
    // +0x14: m_pTableInfo (pointer to TableInfo)

    bool containsString(const char* inputString) {
        char* str = const_cast<char*>(inputString); // function modifies string? normalizeString might modify input.
        uint32_t tokenCount = 0;
        int tokenList[3] = {0};
        void (*cleanupFunc1)(void*) = nullptr;  // local_4 – uninitialized in decompilation, but used
        void (*cleanupFunc2)(void*) = nullptr;  // local_14 – same

        // Step 1: Normalize the string (e.g., to lowercase, strip whitespace)
        normalizeString(str);

        // Step 2: Parse the string into tokens (e.g., split by delimiter)
        // This may set tokenList[0], tokenCount, and also initialize cleanupFunc1/2
        parseTokens(str, tokenList, (int*)&tokenCount); // assumes tokenCount is output

        // If a token was extracted, call cleanup on it later (if needed)
        if (tokenList[0] != 0) {
            if (cleanupFunc1 != nullptr)
                cleanupFunc1((void*)tokenList[0]);
        }

        // If more than 15 tokens? (likely a guard against overflow)
        if (tokenCount > 15) {
            if (tokenCount != 0) {
                if (cleanupFunc2 != nullptr)
                    cleanupFunc2((void*)tokenCount);  // tokenCount used as pointer? Possibly a mistake; may be a pointer to allocated memory.
            }
            return false; // already exists? Or indicates failure
        }

        // Compute hash of the original string (after normalization)
        int len = 0;
        while (str[len] != '\0')
            len++;
        uint32_t stringHash = computeStringHash(str, len);

        // Access the hash table via this+0x14 -> TableInfo
        TableInfo* tableInfo = *(TableInfo**)((uint8_t*)this + 0x14);
        uint16_t entryCount = *(uint16_t*)((uint8_t*)tableInfo + 4);

        if (entryCount != 0) {
            // Get base of the hash entry array: this+4 -> ptr to table, then +0x40 offset
            HashEntry* entries = (HashEntry*)(*(uint8_t**)((uint8_t*)this + 4) + 0x40);

            for (uint16_t i = 0; i < entryCount; i++) {
                if (entries[i].hash == stringHash) {
                    // Found existing entry
                    if (tokenCount != 0) {
                        if (cleanupFunc2 != nullptr)
                            cleanupFunc2((void*)tokenCount);
                    }
                    return false; // string already registered
                }
            }
        }

        // Not found
        if (tokenCount != 0) {
            if (cleanupFunc2 != nullptr)
                cleanupFunc2((void*)tokenCount);
        }
        return true; // string not present, can be added
    }
};