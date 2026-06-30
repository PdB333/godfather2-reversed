// FUNC_NAME: HashTable::removeAndFreeNode
#include <cstdint>

// Hash table with a free list for recycled nodes.
// Structure layout (param_1):
// +0x00: Node** table          (array of head pointers to buckets)
// +0x04: int32_t tableSize     (number of buckets)
// +0x08: Node* freeList        (head of singly-linked free list)
// +0x0C: int32_t count         (number of nodes in table, including free?)
// Node layout (offset 6 = next pointer at +0x18 from node start):
// +0x00: uint32_t key
// +0x18: Node* next

class HashTable {
private:
    struct Node {
        uint32_t key;      // +0x00
        // other fields up to offset 0x18 (not used here)
        Node* next;        // +0x18
    };

    Node** table;          // +0x00
    int32_t tableSize;     // +0x04
    Node* freeList;        // +0x08
    int32_t count;         // +0x0C

public:
    // __thiscall at 0x00448630
    // Looks up a node by key. If found, removes it from its bucket
    // and moves it to the front of the free list. Returns false if found,
    // true if key not present.
    bool removeAndFreeNode(uint32_t key) {
        uint32_t index = key % tableSize;
        Node* bucket = table[index];
        Node* prev = nullptr;

        while (bucket) {
            if (bucket->key == key) {
                // Unlink from bucket
                if (prev) {
                    prev->next = bucket->next;
                } else {
                    table[index] = bucket->next;
                }

                // Move to free list head
                bucket->next = freeList;
                freeList = bucket;
                count--;
                return false;  // found
            }
            prev = bucket;
            bucket = bucket->next;
        }

        return true;  // not found
    }
};