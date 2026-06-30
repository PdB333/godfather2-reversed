// FUNC_NAME: Cache::lookupAndMoveToFront

#include <cstdint>

// The key structure passed in EAX (3-part key: two shorts + int)
struct CacheKey {
    uint16_t keyPart1;   // offset 0x00
    uint16_t keyPart2;   // offset 0x02
    int32_t  keyPart3;   // offset 0x04
};

// Node structure for the hash table / LRU list
// Layout deduced from offsets used in the code
struct CacheNode {
    // offset 0x00: unknown/could be tombstone
    CacheNode* hashNext;       // +0x04: next in hash chain (linked list for bucket)
    // offset 0x08: unknown
    CacheNode* lruPrev;        // +0x0c: previous in LRU doubly linked list
    CacheNode* lruNext;        // +0x10: next in LRU doubly linked list
    // ... padding/other fields ...
    uint16_t key1;             // +0x60: first key short
    uint16_t key2;             // +0x62: second key short
    int32_t  key3;             // +0x64: third key (int)
    // value is likely stored after the key
};

// Cache object (this pointer in ECX)
// Fields:
//   +0x0c: hashTableBase (pointer to array of 128 bucket heads)
//   +0x14: lruHead (head of LRU list, most recently used)
//   +0x18: lruTail (tail of LRU list, least recently used)
struct Cache {
    // other fields ...
    CacheNode** hashTable;    // +0x0c: array of 128 pointers to first node in bucket
    CacheNode*  lruHead;      // +0x14: most recently used node
    CacheNode*  lruTail;      // +0x18: least recently used node
    // ...
};

// Function at 0x00672a80
// Called with this in ECX (Cache*) and a pointer to a CacheKey in EAX.
// Does a hash lookup using the 3-part key, then moves the found node to the front of the LRU list.
void __fastcall Cache::lookupAndMoveToFront(Cache* thisPtr)
{
    // The key structure is passed in EAX – we declare it as a local reference for clarity
    CacheKey* key; // actually in EAX, but we treat it as a parameter for reconstruction
    // Note: In the actual calling convention, EAX holds the key pointer.
    // For readability, we assume 'key' is the value that was in EAX.
    // Ghidra's decompiler uses 'in_EAX' to represent this.
    // We'll inline the usage below.

    // Compute bucket index: (key1 * 16 + key3 + key2) & 0x7f (128 buckets)
    uint32_t bucketIndex = (static_cast<uint32_t>(key->keyPart1) * 0x10 +
                            static_cast<uint32_t>(key->keyPart3) +
                            static_cast<uint32_t>(key->keyPart2)) & 0x7f;

    // Get the first node in the bucket
    CacheNode* node = thisPtr->hashTable[bucketIndex];

    if (node != nullptr) {
        // Walk the hash chain until we find a node matching all three key fields
        while (node->key2 != key->keyPart2 ||
               node->key1 != key->keyPart1 ||
               node->key3 != key->keyPart3) {
            node = node->hashNext;
            if (node == nullptr) {
                return; // key not found
            }
        }

        // If node is already at the head of the LRU list, nothing to do
        if (node != thisPtr->lruHead) {
            // Unlink node from its current position in the doubly linked list
            if (node == thisPtr->lruTail) {
                // Node is the tail: update tail to its predecessor
                thisPtr->lruTail = node->lruPrev;
            } else {
                // Node is not the tail: link its predecessor to its successor
                node->lruPrev->lruNext = node->lruNext;
            }
            // Link successor's prev pointer to the predecessor
            node->lruNext->lruPrev = node->lruPrev;

            // Insert node at the head of the LRU list
            node->lruNext = thisPtr->lruHead;
            thisPtr->lruHead->lruPrev = node;
            thisPtr->lruHead = node;
            node->lruPrev = nullptr; // head has no previous
        }
    }
}