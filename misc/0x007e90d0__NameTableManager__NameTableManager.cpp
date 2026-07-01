// FUNC_NAME: NameTableManager::NameTableManager

// Reconstructed constructor for NameTableManager at 0x007e90d0
// This initializes a hash table for string-to-ID mapping with 69 predefined entries.
// Singleton instance stored at DAT_011298ac.

class NameTableManager {
public:
    // Vtable pointers assumed, but structure is manually initialized
    // Offset 0x00: vtable pointer (set to FUN_00d6fd74)
    // Offset 0x04: vtable pointer 2? (set to FUN_00e2f19c, then LAB_00d6fd64)
    // Offset 0x08: field2 = 1
    // Offset 0x0C: field3 = 0
    // Offset 0x10: field4 = &LAB_00d6fd5c then &LAB_00d6fd60
    // Offset 0x14: byte flag m_registered (0 or 1)
    // Offset 0x18: padding? (not used)
    // Offset 0x20: m_entries[69] each 12 bytes (3 ints) starting at offset 0x20? Actually param_1+8 is offset 8*4=0x20. But they set puVar5 = param_1+8, so offset 0x20.
    // Offset 0x354: m_hashResults[69] each 8 bytes (2 ints) starting at offset 0x354? Because param_1+0xd5 -> offset 0xd5*4=0x354. But they set puVar9 = param_1+0xd5, so 0x354.

    struct HashTable {
        int* buckets;       // +0x00
        int size;           // +0x04
        int* freeListHead;  // +0x08
        int count;          // +0x0C
        int something;      // +0x10 (used as head pointer? set during init)
        char growFlag;      // +0x14 (low byte of +0x14)
    };

    struct Entry {
        int isInitialized; // always 1
        int someGlobal;    // from DAT_00d5780c
        int constant10;    // always 10
    };

    struct HashResult {
        int value1; // always 0
        int value2; // always 0
    };

    Entry m_entries[69];     // offset 0x20 (param_1+8)
    HashResult m_hashResults[69]; // offset 0x354 (param_1+0xd5)
    char m_registered;       // offset 0x14 (param_1[5] as byte)

    // Other fields after the array: offsets 0x75C (param_1[0x1d7]) and 0x760 (param_1[0x1d8]) etc.

    // Vtable and vtable-related pointers are set inline
};

void* __thiscall NameTableManager::NameTableManager(NameTableManager* this, int param2)
{
    // Two vtable pointers? Possibly multiple inheritance or RTTI
    *(int*)this[1] = (int)&PTR_FUN_00e2f19c; // +0x04
    this[2] = 1;                              // +0x08
    this[3] = 0;                              // +0x0C
    *(int*)this[4] = (int)&PTR_LAB_00d6fd5c; // +0x10

    DAT_011298ac = this; // store singleton pointer

    *(int*)this[0] = (int)&PTR_FUN_00d6fd74; // +0x00 vtable
    *(int*)this[1] = (int)&PTR_LAB_00d6fd64; // override +0x04
    *(int*)this[4] = (int)&PTR_LAB_00d6fd60; // override +0x10
    *((char*)this + 0x14) = 0;               // m_registered = 0

    // Initialize 19 slots for something? Actually loop 19 times (0x13)
    int* slot = (int*)(this + 0x15f); // offset 0x15f*4 = 0x57C
    for (int i = 0; i < 19; i++) {
        slot[0] = 0;
        slot[1] = 1;
        slot[2] = 0;
        slot[3] = 0;
        slot[4] = 0;
        slot[5] = 0;
        slot += 6;
    }

    // Set three more fields at offset 0x1d7, 0x1d8, 0x1d9 (0x75C, 0x760, 0x764)
    this[0x1d7] = 0;
    this[0x1d8] = 0;
    this[0x1d9] = 0;

    // Allocate hash table structure
    int* allocResult = (int*)FUN_009c8e50(0x18); // allocate 24 bytes
    int** hashTable;
    if (allocResult == 0) {
        hashTable = 0;
    } else {
        // FUN_007e83f0 initializes a hash table with 0x20 buckets and flag 0
        hashTable = (int**)FUN_007e83f0(0x20, 0);
    }
    DAT_0112bb2c = hashTable;

    // Initialize 69 predefined entries (hash table bucket inserts)
    HashResult* hr = (HashResult*)(this + 0xd5); // offset 0x354
    Entry* entry = (Entry*)(this + 8);          // offset 0x20
    for (uint i = 0; i < 0x45; i++) {
        uint hashVal = (&DAT_00d6fc18)[i]; // table of 69 hash values
        if (hashVal != 0) {
            // Insert into hash table
            uint bucketIdx = hashVal % hashTable[1]; // size
            if ( ((char)hashTable[5] != 0) && (hashTable[1] * 2 <= hashTable[3]) ) {
                FUN_007e8480(); // rehash
                bucketIdx = hashVal % hashTable[1];
            }
            int* bucketList = (int*)hashTable[2]; // free list? Actually head of chain?
            if (bucketList == 0) {
                // Allocate a new block of nodes (256 nodes of 12 bytes each + 4 extra = 0xc04)
                int* newNodeBlock = (int*)FUN_009c8e50(0xc04);
                for (int j = 0; j < 0xff; j++) {
                    newNodeBlock[3] = (int)(newNodeBlock + 4); // link nodes
                }
                newNodeBlock[0x300] = 0; // last node's next is null
                *newNodeBlock = hashTable[4]; // attach to bucket list
                hashTable[4] = (int)newNodeBlock;
                bucketList = newNodeBlock + 1; // first usable node
                hashTable[2] = (int)bucketList;
            }
            // Remove next from free list
            hashTable[2] = bucketList[2];
            bucketList[2] = 0;
            hashTable[3]++; // count
            bucketList[1] = i; // stored index
            bucketList[0] = hashVal;
            bucketList[2] = ((int*)hashTable[0])[bucketIdx]; // old head
            ((int*)hashTable[0])[bucketIdx] = (int)bucketList;
        }

        // Initialize corresponding entries
        hr->value1 = 0;
        hr->value2 = 0;
        entry->isInitialized = 1;
        entry->someGlobal = _DAT_00d5780c; // likely a global or static value
        entry->constant10 = 10;

        hr++;
        entry++;
    }

    // Register this manager with a global hash (0xded51537)
    int local_4 = 0;
    int result = FUN_00463a80(0xded51537, &local_4);
    if (result == 0) {
        *((char*)this + 0x14) = 1; // m_registered = 1
        FUN_00463980(0xded51537, this, param2); // register callback
    }

    return this;
}