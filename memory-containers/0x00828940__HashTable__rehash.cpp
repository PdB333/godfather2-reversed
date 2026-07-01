// FUNC_NAME: HashTable::rehash
// 0x00828940: Rehash hash table to new bucket count (EASTL-based allocator)
// Struct members: +0x04 m_pBuckets (uint**), +0x08 m_bucketCount (uint)

#include <cstddef>
#include <cstring>

// Allocator function from EASTL debug build
extern "C" void* __cdecl FUN_0068ab90(size_t size, const char* name, int flags, int /*unused*/,
    const char* file, int line);

// Deallocator function
extern "C" void __cdecl FUN_009c8f10(void* ptr);

struct HashNode {
    unsigned int hash;   // +0x00
    // +0x04: possibly value or padding
    HashNode* next;      // +0x08
};

void __thiscall HashTable::rehash(unsigned int newBucketCount) {
    size_t newSize = newBucketCount * 4;                  // array of 4-byte pointers
    unsigned int** newBuckets = (unsigned int**)FUN_0068ab90(
        newSize + 4, "EASTL", 0, 0,
        "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);

    memset(newBuckets, 0, newSize);                       // zero the bucket array
    *(unsigned int*)((char*)newBuckets + newSize) = 0xFFFFFFFF; // sentinel after array

    unsigned int oldCount = this->m_bucketCount;
    if (oldCount != 0) {
        unsigned int i = 0;
        do {
            unsigned int* node = this->m_pBuckets[i];     // head of old bucket
            while (node != nullptr) {
                unsigned int hash = *node;                // first field is hash/key
                this->m_pBuckets[i] = (unsigned int*)node[2]; // advance head to next node (offset +8)
                node[2] = (unsigned int)newBuckets[hash % newBucketCount]; // link into new bucket
                newBuckets[hash % newBucketCount] = node;
                node = this->m_pBuckets[i];
            }
            i++;
        } while (i < oldCount);
    }

    // Free old bucket array if it had more than one bucket
    if (oldCount > 1) {
        FUN_009c8f10(this->m_pBuckets);
    }

    this->m_pBuckets = newBuckets;
    this->m_bucketCount = newBucketCount;
}