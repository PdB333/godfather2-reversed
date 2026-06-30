// FUNC_NAME: HashTable::insertEntry

#include <cstdint>

// Forward declarations
class MemoryManager;
struct HashTable;
struct HashNode;

// Global hash table pointer (from DAT_01223398)
extern HashTable* g_pHashTable;

// Memory manager singleton (from FUN_009c8f80)
MemoryManager* getMemoryManager();

// Initialize allocated block (from FUN_0050e790)
uint32_t initializeBlock(uint32_t param1, uint32_t param2);

// Rehash the hash table (from FUN_00423fa0)
void rehashHashTable();

// Allocate a new hash node (from FUN_00423f20)
HashNode* allocateHashNode();

// Memory allocation parameters
struct AllocationParams {
    uint32_t flags;    // +0x0
    uint32_t alignment; // +0x4
    uint32_t unknown;   // +0x8
};

// Memory manager interface (vtable-based)
class MemoryManager {
public:
    virtual uint32_t allocate(uint32_t size, AllocationParams* params) = 0;
    // ... other virtual methods
};

// Hash table structure (matching DAT_01223398 layout)
struct HashTable {
    uint32_t field_0;          // +0x00
    HashNode** buckets;        // +0x04
    uint32_t bucketCount;      // +0x08
    uint32_t capacity;         // +0x10
    int8_t   rehashFlag;       // +0x18
    // ... other fields
};

// Hash node for chaining
struct HashNode {
    uint32_t key;             // +0x00
    uint32_t value;           // +0x04
    HashNode* next;           // +0x08
};

// Main function: allocate a block and insert it into the global hash table
void HashTable::insertEntry(uint32_t key, uint32_t sizeDescriptor, int32_t objectPtr,
                            uint32_t extraArg1, uint32_t extraArg2)
{
    // Extract slot count from high 16 bits of sizeDescriptor
    int16_t slotCount = static_cast<int16_t>(sizeDescriptor >> 16);

    // Compute aligned block size: base size = slots * 8 + 0x8F, rounded up to 16
    uint32_t blockSize = (slotCount * 8 + 0x8F) & 0xFFFFFFF0;

    // If the object has a special flag (6) at offset 0x154, add extra space for slots*32
    if (*(char*)(objectPtr + 0x154) == 6) {
        blockSize += slotCount * 0x20;
    }

    // Get memory manager
    MemoryManager* memMgr = getMemoryManager();

    // Prepare allocation parameters
    AllocationParams allocParams;
    allocParams.flags = 2;
    allocParams.alignment = 0x10;
    allocParams.unknown = 0;

    // Attempt to allocate the block
    uint32_t allocatedBlock = memMgr->allocate(blockSize, &allocParams);
    if (allocatedBlock == 0) {
        blockSize = 0;
    } else {
        // Initialize the block (function takes two additional arguments)
        blockSize = initializeBlock(extraArg1, extraArg2);
    }

    // Zero out the table at the start of the block (offset 0x80, size = slotCount * 2 dwords)
    uint32_t* tablePtr = reinterpret_cast<uint32_t*>(blockSize + 0x80);
    int tableItems = slotCount;
    while (tableItems > 0) {
        tablePtr[0] = 0;
        tablePtr[1] = 0;
        tablePtr += 2;
        tableItems--;
    }

    // If the object's flag is 6, set up an extra pointer table
    if (*(char*)(objectPtr + 0x154) == 6) {
        // Set offset +0x54 to point to allocatedBlock + (some base offset from register)
        // Note: unaff_EBX is a register holding a base offset (likely from objectPtr)
        *(uint32_t*)(blockSize + 0x54) = allocatedBlock + /*unaff_EBX*/ 0; // actual base unknown

        // Zero out the table at that address: slotCount*8 ints
        int* extraTable = reinterpret_cast<int*>(*(uint32_t*)(blockSize + 0x54));
        int extraItems = slotCount * 8;
        for (int i = 0; i < extraItems; ++i) {
            extraTable[i] = 0;
        }
    }

    // Access global hash table
    HashTable* hashTable = g_pHashTable; // from DAT_01223398 + 8

    // Compute bucket index from key
    uint32_t bucketIndex = key % hashTable->bucketCount;

    // Check if rehashing is needed
    if (hashTable->rehashFlag && (hashTable->bucketCount * 2 <= hashTable->capacity)) {
        rehashHashTable();
        bucketIndex = key % hashTable->bucketCount;
    }

    // Allocate a new hash node
    HashNode* newNode = allocateHashNode();
    newNode->value = blockSize;   // store the allocated block address
    newNode->key = key;           // store the key
    // Link into bucket chain
    newNode->next = hashTable->buckets[bucketIndex];
    hashTable->buckets[bucketIndex] = newNode;

    return;
}