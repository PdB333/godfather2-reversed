// FUN_NAME: MessageManager::sendMessage
#include <cstdint>

// Internal hash table node structure (from decompilation)
struct HashNode {
    uint32_t key;          // +0x00
    void* dataPointer;     // +0x04
    HashNode* next;        // +0x08
};

// Hash table descriptor (pointed to by global manager +8)
struct HashTable {
    HashNode** buckets;    // +0x04
    uint32_t bucketCount;  // +0x08
};

// Global manager structure (base at DAT_01223398)
struct GlobalManager {
    uint8_t pad[8];        // unused fields
    HashTable* hashTable;  // +0x08
};

// Reference to the global manager (address 0x01223398)
extern GlobalManager* g_manager;

// Forward declaration of the actual delegate caller (FUN_00940d50)
extern uint32_t* callDelegateFunction(uint32_t param2, uint32_t param3, uint32_t* dataBuffer, 
                                      uint32_t param5, uint32_t param6, void* extraPtr);

/**
 * Dispatches a message by key.
 * Looks up a hash table entry using param1 (key), copies 64 bytes (16 dwords) from param4,
 * then invokes the stored delegate function via callDelegateFunction.
 */
uint32_t* MessageManager::sendMessage(uint32_t key, 
                                     uint32_t param2, 
                                     uint32_t param3, 
                                     uint32_t* dataPtr, 
                                     uint32_t param5, 
                                     uint32_t param6)
{
    // Get the hash table descriptor
    HashTable* ht = g_manager->hashTable;
    uint32_t numSlots = ht->bucketCount;
    uint32_t slotIndex = key % numSlots;

    // Locate the bucket head
    HashNode* node = ht->buckets[slotIndex];
    if (!node) {
        return nullptr;
    }

    // Traverse the linked list for the matching key
    while (node->key != key) {
        node = node->next;
        if (!node) {
            return nullptr;
        }
    }

    // Node found; get the data pointer stored in the node
    uint32_t* valuePtr = static_cast<uint32_t*>(node->dataPointer);
    if (!valuePtr) {
        return nullptr;
    }

    // Copy 16 dwords (64 bytes) from the caller's data buffer into a local array
    uint32_t localCopy[16]; // local_50 in decompiled code (actually 19 dwords allocated, but only 16 used)
    for (int i = 0; i < 16; ++i) {
        localCopy[i] = dataPtr[i];
    }

    // Invoke the delegate with the copied data.
    // The last argument (&stack0x0000001c) is the address immediately after the 16 dwords,
    // possibly used for additional output or a continuation pointer.
    valuePtr = callDelegateFunction(param2, param3, localCopy, param5, param6, &localCopy[16]);

    return valuePtr;
}