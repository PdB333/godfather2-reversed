// FUNC_NAME: ResourceHashTable::setEntry
// Address: 0x005e7b20
// Purpose: Sets a value in a global hash table keyed by a hashed ID.
// The table is stored at g_resourceHashTable (DAT_01223504).
// Hash key is computed as (inputId XOR 0xAD103100). The table has a maximum
// size (byte at +0x1c) and an array of pointers at +0x04 (indexed by low byte).
// If the pointer at that index is non-null, the value (param_2) is written
// at offset +0x6c of that structure.

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;

// Global hash table structure
struct HashTable {
    byte maxEntries;       // +0x1c: max number of entries
    byte padding[3];
    void* entries[256];    // +0x04: array of pointers to entry structures
                           // (actually size unknown, but indexed by low byte)
};

// Simulated global variable (from DAT_01223504)
extern HashTable* g_resourceHashTable;

// Each entry structure (size >= 0x70)
struct HashEntry {
    // ... other fields at least up to +0x6c
    uint dataValue;        // +0x6c: value to set
};

// __thiscall convention: this pointer passed in ECX, first param in stack.
// But here param_1 is the hash key, not a this pointer.
// Ghidra misidentified, likely __cdecl or actually a member function of HashTable
// where param_1 is the hash key and param_2 is the value.
// We treat as a regular function taking two parameters.

byte FUN_005e7b20(uint inputHash, uint newValue) {
    byte result = 0;
    uint maskedHash = inputHash ^ 0xAD103100;
    
    // Check if hash is within valid range (maxEntries is byte at +0x1c)
    if (maskedHash < (uint)(g_resourceHashTable->maxEntries)) {
        // Compute index using low byte of maskedHash
        byte index = (byte)maskedHash;
        void** entryPtr = &g_resourceHashTable->entries[index];
        
        // If entry exists, set the value at offset +0x6c
        if (*entryPtr != 0) {
            HashEntry* entry = (HashEntry*)(*entryPtr);
            entry->dataValue = newValue;
            result = 1;
        }
    }
    return result;
}