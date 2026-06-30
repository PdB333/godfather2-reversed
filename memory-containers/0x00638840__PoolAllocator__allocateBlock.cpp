// FUNC_NAME: PoolAllocator::allocateBlock

// Reconstructed C++ for function at 0x00638840
// Role: Allocate a block of memory from a pool, copy data, and insert into a hash table

#include <cstring>

// Forward declarations
void* poolAllocatorMalloc(size_t size);  // Global raw allocator, stored at DAT_012059dc
void reportMemoryError(void* allocator, const char* message); // FUN_00633920
void* handleOutOfMemory(); // FUN_00635a80
void resizeHashTable(void* allocator, int newSize); // FUN_00638740

// Block header structure (16 bytes)
#pragma pack(push, 1)
struct PoolBlock {
    PoolBlock* next;          // +0x00: next free/chain pointer
    uint8_t type;             // +0x04: always 4 for allocated blocks
    uint8_t padding1;         // +0x05: zero
    uint8_t padding2;         // +0x06: zero
    uint8_t reserved;         // +0x07: unused
    uint32_t size;            // +0x08: original size requested (without header)
    uint32_t hash;            // +0x0C: hash value (for bucket lookup)
    // +0x10: start of user data
};
#pragma pack(pop)

// Memory pool structure (at offset +0x10 from allocator)
struct HashTable {
    PoolBlock** buckets;      // pointer to array of bucket heads
    int count;                // number of allocated blocks
    int bucketCount;          // current size of bucket array (power of two)
};

// Allocator class (simplified)
class PoolAllocator {
public:
    void* vtable;             // +0x00
    // ... other members ...
    HashTable* hashTable;     // +0x10

    PoolBlock* allocateBlock(void* data, size_t size, uint32_t hash) {
        size_t totalSize = size + 0x11; // header (16 bytes) + data + null terminator (1 byte)
        PoolBlock* block = nullptr;

        if (totalSize == 0) {
            return nullptr;
        }

        if (totalSize > 0xFFFFFFFD) { // >= 2^32-3? (sanity check)
            reportMemoryError(this, "memory allocation error: block too big");
            return nullptr;
        }

        // Call raw allocator (function pointer from global)
        block = static_cast<PoolBlock*>(poolAllocatorMalloc(totalSize));
        if (block == nullptr) {
            if (this != nullptr) {
                return static_cast<PoolBlock*>(handleOutOfMemory());
            }
            return nullptr;
        }

        // Initialize header
        block->type = 4;
        block->padding1 = 0;
        block->padding2 = 0;
        block->size = size;
        block->hash = hash;

        // Copy user data
        memcpy(block + 1, data, size); // block+1 points to offset 0x10
        // Null-terminate (for string safety)
        *(reinterpret_cast<uint8_t*>(block) + 0x10 + size) = 0;

        // Insert into hash table
        HashTable* ht = this->hashTable;
        uint32_t bucketIndex = hash & (ht->bucketCount - 1);
        block->next = ht->buckets[bucketIndex];
        ht->buckets[bucketIndex] = block;
        ht->count++;

        // Resize if load factor too high
        if (ht->bucketCount < ht->count && ht->bucketCount < 0x3FFFFFFF) {
            resizeHashTable(this, ht->bucketCount * 2);
        }

        return block;
    }
};