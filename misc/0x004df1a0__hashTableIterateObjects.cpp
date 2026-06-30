// FUNC_NAME: hashTableIterateObjects
// Function at 0x004df1a0: Iterates over all objects stored in a hash table and invokes a callback for each.
// The hash table is a global structure: array of bucket pointers + bucket count.
// Each node has a data pointer (passed to callback) and a next pointer.
// Assumes a global iteration state initialized by an internal helper.

#include <cstdint>

// Callback type: takes object data and a user parameter
using ObjectCallback = void (*)(void* objectData, uint32_t userParam);

// Node in a hash table bucket linked list
struct HashNode {
    void* data;         // +0x00
    HashNode* next;     // +0x04
};

// Hash table structure
struct HashTable {
    HashNode** buckets; // +0x00: pointer to array of bucket heads
    uint32_t numBuckets;// +0x04: number of buckets
};

// Global pointer to the hash table (DAT_012054c4)
static HashTable* g_hashTable = reinterpret_cast<HashTable*>(0x012054c4);

// Internal function that resets iteration state (FUN_004e1020)
// It is assumed to set a global or static current pointer and bucket index.
// For reconstruction, we declare it as a void function with no arguments.
void initHashTableIteration();

void hashTableIterateObjects(ObjectCallback callback, uint32_t userParam)
{
    HashTable* table = g_hashTable;
    uint32_t index;               // local_8 – bucket index (initialized by init)
    HashNode* current;            // local_4 – current node (initialized by init)

    // Reset the iteration state; likely sets current to first node and index to 0
    initHashTableIteration();

    // The decompiled code checks if current is non‑null after the call.
    // We assume current is set by initHashTableIteration.
    if (current != nullptr)
    {
        do
        {
            while (true)
            {
                // Invoke callback with the node’s data
                callback(current->data, userParam);
                // Move to the next node in the current bucket chain
                current = current->next;

                // If the table pointer is null (shouldn’t happen), abort iteration
                if (table == nullptr) break;

                // When we reach the end of a bucket chain, find the next non‑empty bucket
                if (current == nullptr)
                {
                    do
                    {
                        if (index >= table->numBuckets) // no more buckets – exit loop
                            goto endIteration;

                        // Load head of the next bucket
                        current = table->buckets[index];
                        index++;
                    } while (current == nullptr); // skip empty buckets
                }
            }

endIteration:
            // The outer loop continues only if we exited the inner while with a non‑null current
            // (i.e., after finding a new bucket head)
            ;
        } while (current != nullptr);
    }
}