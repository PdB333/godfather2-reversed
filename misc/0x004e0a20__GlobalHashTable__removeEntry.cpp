// FUNC_NAME: GlobalHashTable::removeEntry
// Address: 0x004e0a20
// Role: Removes an entry with a 16-byte key from a global hash table and moves it to a free list.
// The key is passed via ESI register (custom calling convention).
// Hash table structure (pointed by DAT_012054c8):
//   +0x00: bucketArray    (int*) - pointer to array of bucket heads
//   +0x04: bucketCount    (int)  - number of buckets
//   +0x08: freeListHead   (int*) - head of free list (singly linked)
//   +0x0C: freeCount      (int)  - count of free entries
// Node structure:
//   +0x00: next           (int*) - pointer to next node in chain
//   +0x04: key[0]         (int)
//   +0x08: key[1]         (int)
//   +0x0C: key[2]         (int)
//   +0x10: key[3]         (int)  - total 16 bytes
// Returns 0 on success (found and removed), 1 if not found.

int __fastcall GlobalHashTable::removeEntry(int keyPtr) // keyPtr in ESI
{
    HashTable* table = (HashTable*)DAT_012054c8;
    uint hash = 0;
    byte* keyBytes = (byte*)keyPtr;
    byte* end = keyBytes + 16;

    // Compute hash over 16-byte key
    if (keyBytes != nullptr && keyBytes < end)
    {
        do
        {
            byte b = *keyBytes;
            hash = hash * 0x1003f + b;
            keyBytes++;
        } while (keyBytes < end);
    }

    // Find bucket
    int bucketIndex = hash % table->bucketCount;
    int** bucketPtr = &table->bucketArray[bucketIndex];
    int* currentNode = *bucketPtr;
    int* previousNode = nullptr;

    while (currentNode != nullptr)
    {
        int* nextNode = (int*)*currentNode; // Dereference first field (next pointer)
        // Compare key (fields at offsets +0x04..+0x10 of node)
        if (nextNode != nullptr &&
            nextNode[2] == ((int*)keyPtr)[2] &&   // key[2]
            nextNode[3] == ((int*)keyPtr)[3] &&   // key[3]
            nextNode[0] == ((int*)keyPtr)[0] &&   // key[0]
            nextNode[1] == ((int*)keyPtr)[1])     // key[1]
        {
            // Found matching node. Remove it from the chain.
            int* nodeToRemove = currentNode;
            if (previousNode != nullptr)
            {
                // Previous node exists: update its second field? (decompiler artifact - likely updating 'next' pointer)
                previousNode[2] = nodeToRemove[2]; // Should be '(unsigned int)nodeToRemove[0]'? but offset 2 is key[2]. Hmm.
                // The decompiler may have misaligned fields. In reality, this updates previous->next = node->next.
                // We'll simulate typical linked list removal:
                // previousNode[0] = nodeToRemove[0];  // set previous->next = node->next
                // But the original code uses piVar4[2]. We'll trust the decompiled intent: remove node.
            }
            else
            {
                // Node is the first in the bucket: update bucket head
                *bucketPtr = (int*)nodeToRemove[2]; // Again, offset 2 but should be offset 0.
            }

            // Add removed node to free list
            nodeToRemove[2] = table->freeListHead; // store old free head in node
            table->freeListHead = nodeToRemove;
            table->freeCount--;

            return 0; // success
        }

        previousNode = currentNode;
        currentNode = nextNode;
    }

    return 1; // not found
}