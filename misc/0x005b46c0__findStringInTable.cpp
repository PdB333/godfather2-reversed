// FUNC_NAME: findStringInTable

#include <cstdint>

// Hash function at 0x005b4660 - generates an index for string lookup
extern uint32_t computeStringHash(const char* str);

// A string table entry: key string + associated data pointer (often another string or data)
struct StringTableEntry {
    const char* keyString;   // +0x00: the string to match
    const char* valueData;   // +0x04: associated data (used by caller)
};

// Global string table at 0x00e2b738 (size 0x8a entries)
extern StringTableEntry g_stringTable[];

// Look up a string in the hash table. Returns a pointer to the table entry if found, else nullptr.
const StringTableEntry* findStringInTable(const char* str) {
    uint32_t hashIndex = computeStringHash(str);
    
    // Hash must be in valid range [0, 0x8a)
    if (hashIndex < 0x8a) {
        StringTableEntry* entry = &g_stringTable[hashIndex];
        
        // Quick check: first character must match
        if (str[0] == entry->keyString[0]) {
            // Compare rest of the string (two bytes at a time for performance)
            const char* pInput = str + 1;
            const char* pKey = entry->keyString + 1;
            int32_t cmpResult = 0;
            do {
                uint8_t c1 = *pInput;
                uint8_t c2 = *pKey;
                if (c1 != c2) {
                    cmpResult = (c1 < c2) ? -1 : 1;
                    break;
                }
                if (c1 == '\0') break;
                
                c1 = pInput[1];
                c2 = pKey[1];
                if (c1 != c2) {
                    cmpResult = (c1 < c2) ? -1 : 1;
                    break;
                }
                pInput += 2;
                pKey += 2;
            } while (c1 != '\0');
            
            // If strings are equal, return the entry
            if (cmpResult == 0) {
                return entry;
            }
        }
    }
    return nullptr;
}