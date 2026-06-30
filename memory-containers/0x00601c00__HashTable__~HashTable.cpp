// FUNC_NAME: HashTable::~HashTable
#include <cstdint>

// Offset definitions for HashTable class (assuming byte offsets)
// this+0x00: vtable pointer
// this+0x04: listHead (pointer to first node in a separate linked list)
// ... (other fields not used)
// this+0x38: buckets pointer (array of bucket structures, each 8 bytes)
// this+0x3C: bucketCount (uint16)

struct Bucket {
    void* head;  // +0x00: pointer to first element in bucket chain
    void* next;  // +0x04: pointer used for list traversal (points back to previous node or bucket)
};

void __fastcall HashTable::~HashTable()
{
    // Set vtable to class-specific function table
    *(void**)this = (void*)&PTR_FUN_00e40838;

    // Read bucket count (uint16 at offset 0x3C)
    uint16_t bucketCount = *(uint16_t*)((char*)this + 0x3C);
    if (bucketCount != 0) {
        Bucket* buckets = *(Bucket**)((char*)this + 0x38);
        for (uint16_t i = 0; i < bucketCount; i++) {
            Bucket* bucket = &buckets[i];
            void* node = bucket->head;
            if (node != nullptr) {
                // Each node has a "link" at offset 4 that may point back to the bucket
                void* link = *((void**)node + 1);
                if (link == bucket) {
                    // If the node's link directly points to this bucket, update it to bucket->next
                    *((void**)node + 1) = bucket->next;
                } else {
                    // Otherwise, traverse the chain starting from link->next to find the bucket
                    void* prev = link;
                    void* curr = *((void**)prev + 1);
                    while (curr != bucket) {
                        prev = curr;
                        curr = *((void**)prev + 1);
                    }
                    // Unlink bucket from the chain
                    *((void**)prev + 1) = bucket->next;
                }
                // Clear the bucket head pointer
                bucket->head = nullptr;
            }
        }
    }

    // Switch vtable to base class (or another) – likely part of destructor ordering
    *(void**)this = (void*)&PTR_FUN_00e32808;

    // Clean up the linked list stored at this+0x04
    void* current = *(void**)((char*)this + 0x04);
    while (current != nullptr) {
        void* next = *((void**)current + 1);
        // Nullify both pointers in the node
        *((void**)current + 1) = nullptr;
        *(void**)current = nullptr;
        current = next;
    }
}