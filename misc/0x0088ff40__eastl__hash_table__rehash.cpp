// FUNC_NAME: eastl::hash_table::rehash
// Function address: 0x0088ff40
// Rehashes the hash table to a new bucket count. Moves all existing nodes into new buckets.
// Uses EASTL allocator for memory management.

#include <cstdint>
#include <cstring>

// Forward declarations for EASTL allocator functions (from EASTL/allocator.h)
void* allocateMemory(size_t size, const char* name, int flags, int align, const char* file, int line);
void deallocateMemory(void* ptr);

struct HashNode {
    uint32_t key;      // +0x00
    // value (not used in rehash)
    HashNode* next;    // +0x08
};

class HashTable {
public:
    // Rehash to new bucket count
    void rehash(uint32_t newBucketCount) {
        size_t bucketArraySize = newBucketCount * sizeof(HashNode*);
        // Allocate new bucket array with sentinel at end
        HashNode** newBuckets = (HashNode**)allocateMemory(
            bucketArraySize + 4,
            "EASTL",
            0, 0,
            "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h",
            0xe9
        );
        memset(newBuckets, 0, bucketArraySize);
        // Set sentinel value at end of allocation (unused but present)
        *(uint32_t*)((uint8_t*)newBuckets + bucketArraySize) = 0xFFFFFFFF;

        // Iterate over old buckets and rehash each node
        for (uint32_t oldBucketIdx = 0; oldBucketIdx < mBucketCount; ++oldBucketIdx) {
            HashNode* node = mBucketArray[oldBucketIdx];
            while (node != nullptr) {
                HashNode* nextNode = node->next; // Save next before modifying
                uint32_t newBucketIdx = node->key % newBucketCount;
                // Insert at head of new bucket
                node->next = newBuckets[newBucketIdx];
                newBuckets[newBucketIdx] = node;
                node = nextNode;
            }
        }

        // Free old bucket array if it had more than one bucket
        if (mBucketCount > 1) {
            deallocateMemory(mBucketArray);
        }

        // Update members
        mBucketArray = newBuckets;
        mBucketCount = newBucketCount;
    }

private:
    HashNode** mBucketArray; // +0x04
    uint32_t mBucketCount;   // +0x08
};