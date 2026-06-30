// FUNC_NAME: createHashTable

// Function at 0x0055c3b0: Allocates and initializes a hash table with separate key/value dynamic arrays.
// Uses a config object (param_2) to obtain the initial capacity via a virtual call at vtable+0x220.
// The table stores keys of size 0x30 (48 bytes) and values of size 0xc (12 bytes).
// Initializes all slots with a sentinel value (DAT_00e2e780, likely ~0x80000000).
// Registers the new table with a parent manager (param_1) via FUN_00546960, then calls FUN_0055c5b0.

#include <cstdint>

// Forward declarations of known engine functions.
extern "C" void* TlsGetValue(uint32_t index);
extern "C" void* FUN_00aa2680(uint32_t size, uint32_t poolTag); // Allocates memory with given pool tag
extern "C" void  FUN_00aa4110(void** buffer, int newCapacity, int elementSize); // Reallocates buffer
extern "C" void  FUN_00546960(void* parent, void* hashTable); // Registers table with parent
extern "C" void  FUN_0055c5b0(void* hashTable); // Further initialization

// External data references
extern uint32_t DAT_01139810; // TLS index
extern uint32_t DAT_00e2e780; // Sentinel value (likely 0x80000000)
extern void*    PTR_FUN_00dc5428; // Vtable for this class

// Structure of the hash table (size 0x20 = 32 bytes)
struct HashTable {
    void** vtable;                  // +0x00
    uint16_t keyElementSize;        // +0x04 (set to 0x20 = 32, but actual key size is 0x30)
    uint16_t unknownShort;          // +0x06 (set to 1)
    int field_8;                    // +0x08 (unused in this function)
    int count;                      // +0x0C (number of elements currently stored)
    int keyCapacity;                // +0x10 (capacity of key buffer, high bit = owned flag)
    void* keyBuffer;                // +0x14 (pointer to key array)
    int valueCapacityOrSize;        // +0x18 (used for value buffer capacity)
    void* valueBuffer;              // +0x1C (pointer to value array)
};

// Config object interface used by this function.
struct HashTableConfig {
    virtual int getInitialCapacity() = 0; // Offset 0x220 in vtable = 136th (since 0x220/4 = 0x88)
};

void* __cdecl createHashTable(void* parent, HashTableConfig* config) {
    // TLS access (likely for memory allocation tracking)
    TlsGetValue(DAT_01139810);

    // Allocate the hash table object (32 bytes, pool tag 0xb)
    HashTable* table = (HashTable*)FUN_00aa2680(0x20, 0xb);

    // Initialize basic fields
    table->keyElementSize = 0x20;          // +0x04
    table->unknownShort = 1;               // +0x06
    table->field_8 = 0;                    // +0x08
    table->count = 0;                      // +0x0C (will be overwritten later)
    table->keyCapacity = 0x80000000;       // +0x10 (high bit signals owned)
    table->vtable = &PTR_FUN_00dc5428;     // +0x00
    table->keyBuffer = nullptr;            // +0x14
    table->valueBuffer = nullptr;          // +0x1C
    table->valueCapacityOrSize = 0x80000000;// +0x18

    // Obtain initial capacity from config virtual function
    int initialCapacity = config->getInitialCapacity();

    // Allocate key buffer (if needed) with element size 0x30
    if ((table->keyCapacity & 0x3FFFFFFF) < initialCapacity) {
        int newCap = (table->keyCapacity & 0x3FFFFFFF) * 2;
        if (newCap <= initialCapacity) {
            newCap = initialCapacity;
        }
        FUN_00aa4110(&table->keyBuffer, newCap, 0x30);
    }
    table->count = initialCapacity; // Actually sets count to capacity? No, it's used as capacity later.

    // Allocate value buffer (if needed) with element size 0xc
    if ((table->valueCapacityOrSize & 0x3FFFFFFF) < initialCapacity) {
        int newCap = (table->valueCapacityOrSize & 0x3FFFFFFF) * 2;
        if (newCap <= initialCapacity) {
            newCap = initialCapacity;
        }
        FUN_00aa4110(&table->valueBuffer, newCap, 0xc);
    }

    // Sentinel value for empty slots
    uint32_t sentinel = DAT_00e2e780;

    // Bulk initialization: 4 elements per iteration (interleaved key/value writes)
    int i = 0;
    if (initialCapacity > 3) {
        int bulkCount = (initialCapacity - 4) / 4 + 1;
        int valueOffset = 0;
        int keyOffset = 0;
        for (int j = 0; j < bulkCount; j++) {
            // Initialize 4 value slots (each 0xc bytes) in the value buffer
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x00) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x04) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x08) = sentinel;
            *(uint32_t*)((uint8_t*)table->keyBuffer   + keyOffset + 0x20)   = sentinel;

            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x0C) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x10) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x14) = sentinel;
            *(uint32_t*)((uint8_t*)table->keyBuffer   + keyOffset + 0x50)   = sentinel;

            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x18) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x1C) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x20) = sentinel;
            *(uint32_t*)((uint8_t*)table->keyBuffer   + keyOffset + 0x80)   = sentinel;

            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x24) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x28) = sentinel;
            *(uint32_t*)((uint8_t*)table->valueBuffer + valueOffset + 0x2C) = sentinel;
            *(uint32_t*)((uint8_t*)table->keyBuffer   + keyOffset + 0xB0)   = sentinel;

            valueOffset += 0x30; // 4 value slots (4 * 0xc = 0x30)
            keyOffset   += 0xC0; // 4 key slots (4 * 0x30 = 0xC0)
        }
        i = bulkCount * 4; // number of elements initialized in bulk
    }

    // Handle remaining elements (<4)
    int valueRem = i * 0x0C;
    int keyRem   = i * 0x30;
    for (; i < initialCapacity; i++) {
        *(uint32_t*)((uint8_t*)table->valueBuffer + valueRem + 0x00) = sentinel;
        *(uint32_t*)((uint8_t*)table->valueBuffer + valueRem + 0x04) = sentinel;
        *(uint32_t*)((uint8_t*)table->valueBuffer + valueRem + 0x08) = sentinel;
        *(uint32_t*)((uint8_t*)table->keyBuffer   + keyRem   + 0x20) = sentinel;

        valueRem += 0x0C;
        keyRem   += 0x30;
    }

    // Registration and final initialization
    FUN_00546960(parent, table);
    FUN_0055c5b0(table);

    return table;
}