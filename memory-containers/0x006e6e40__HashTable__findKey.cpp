// FUNC_NAME: HashTable::findKey
// This function searches a hash table for an entry matching the given 16-byte key.
// The hash table uses separate chaining with linked list nodes.
// Node structure: { void* data; Node* next; }
// Data structure has key fields at offsets 0x10, 0x14, 0x18, 0x1c.
// Note: FUN_004d9af0 is likely a critical section lock/unlock; the unlock may be elsewhere.
// FUN_004db320 is a hash function for 16 bytes.

void __thiscall HashTable::findKey(void *thisPtr, const int *key)
{
    int bucketIndex;
    int hashCode;
    struct Node *currentNode;

    // Copy the 16-byte key onto the stack for hashing
    int keyCopy[4];
    keyCopy[0] = key[0];
    keyCopy[1] = key[1];
    keyCopy[2] = key[2];
    keyCopy[3] = key[3];

    // Acquire a lock (spinlock / mutex) – actual implementation unknown
    criticalSectionLock();

    // Compute hash of the key (16 bytes)
    hashCode = hashBytes(&keyCopy, 16);

    // Get the bucket array from the hash table object
    int *bucketArray = *(int **)(thisPtr);                    // +0x00: pointer to array of bucket heads
    int numBuckets = *(int *)((char *)thisPtr + 4);           // +0x04: number of buckets

    bucketIndex = hashCode % numBuckets;
    currentNode = (Node *)bucketArray[bucketIndex];

    // Walk the linked list in the chosen bucket
    while (currentNode != nullptr)
    {
        // The node stores a pointer to the actual data structure
        int *dataPtr = (int *)currentNode->data;              // node->data is the first field

        // The key fields are at offsets 0x10, 0x14, 0x18, 0x1c within the data struct
        if (dataPtr[4] == key[0] &&    // +0x10
            dataPtr[5] == key[1] &&    // +0x14
            dataPtr[6] == key[2] &&    // +0x18
            dataPtr[7] == key[3])      // +0x1c
        {
            // Key found – early return (no further action)
            return;
        }

        currentNode = currentNode->next;  // node->next is at offset +0x04 from node
    }

    // Key not found – simply return
    return;
}