// FUNC_NAME: DataStore::addData
// Function address: 0x00638840
// Purpose: Allocates a data block, copies data, and inserts it into a hash table.
// The hash table structure is at +0x10 in the DataStore object.
// Hash is passed in EAX (implicit __thiscall register).

#include <cstdint>
#include <cstring>

// Global allocator function pointer (from DAT_012059dc)
extern "C" void* (*g_allocator)(int align, size_t size); // likely malloc

// Forward declarations
void DataStore::resizeHashTable(int newCapacity); // FUN_00638740
void DataStore::allocationError(const char* msg); // FUN_00633920
void* DataStore::fallbackAlloc(); // FUN_00635a80

// Block header layout: 16 bytes header before data
struct DataBlock {
    DataBlock* next;    // +0x00: next in bucket chain
    uint8_t flags;      // +0x04: always 4 (possibly type marker)
    uint8_t unknown5;   // +0x05: 0
    uint8_t unknown6;   // +0x06: 0
    uint32_t hash;      // +0x08: hash key
    size_t size;        // +0x0C: size of data (excluding header)
    // data starts at +0x10 (flexible array member)
    char data[1];
};

// Hash table internal structure (referenced from DataStore at +0x10)
struct HashTable {
    DataBlock** buckets;       // +0x00
    int count;                 // +0x04
    int capacityMask;          // +0x08 (capacity - 1, power of two)
    int totalAllocatedBytes;   // +0x24
};

// This function assumes __thiscall: this in ECX, param2 in EDX, param3 on stack, hash in EAX
DataBlock* DataStore::addData(void* data, size_t size, uint hash) {
    size_t totalSize = size + 0x11; // header (16) + null terminator (1)
    DataBlock* block = nullptr;

    if (totalSize == 0) {
        // size is (size_t)-1? wrap to zero? but check below.
        return nullptr;
    }

    if (totalSize > 0xFFFFFFFD) { // too large
        this->allocationError("memory allocation error: block too big");
        return nullptr;
    }

    // Allocate from global allocator
    block = (DataBlock*)(*g_allocator)(0, totalSize);
    if (block == nullptr) {
        if (this != nullptr) {
            // Fallback allocation attempt
            return (DataBlock*)this->fallbackAlloc();
        }
        return nullptr;
    }

    // Update total allocated bytes in hash table
    HashTable* ht = *(HashTable**)((uint8_t*)this + 0x10);
    // Increment totalAllocatedBytes at offset 0x24 in hash table
    *(int*)((uint8_t*)ht + 0x24) += totalSize;

    // Initialize block fields
    block->size = size;
    block->hash = hash;
    block->flags = 4;          // offset +4
    block->unknown5 = 0;       // offset +5
    block->unknown6 = 0;       // offset +6

    // Copy data into block (starting at offset 0x10)
    memcpy(block->data, data, size);
    // Null-terminate after data (offset 0x10 + size)
    *(uint8_t*)(block->data + size) = 0;

    // Insert into hash table bucket
    uint bucketIndex = hash & ht->capacityMask;
    block->next = ht->buckets[bucketIndex];
    ht->buckets[bucketIndex] = block;

    // Increment count
    ht->count++;

    // Resize if load factor exceeds (count > capacityMask)
    int capacity = ht->capacityMask + 1;
    if (capacity < ht->count && capacity < 0x3FFFFFFF) {
        this->resizeHashTable(capacity * 2);
    }

    return block;
}