// FUNC_NAME: HashTable::removeNode
int __thiscall HashTable::removeNode(int this_int, int key1, int key2, int key3, int key4)
{
    int *bucketHead;
    int *current;
    int *prev;

    // Hash function: key1 + key4 -> mod tableSize
    int tableSize = *(int *)(this_int + 4);                          // +0x04: size of hash table
    int hash = (uint)(key1 + key4) % tableSize;
    int **bucketArray = *(int ***)(this_int + 8);                    // +0x08: pointer to array of bucket heads
    bucketHead = bucketArray[hash];

    current = bucketHead;
    prev = nullptr;
    if (current == nullptr) {
        return 1; // not found
    }

    // Traverse linked list in bucket to find node matching all four keys
    while (current[0] != key1 || current[1] != key2 || current[2] != key3 || current[3] != key4) {
        prev = current;
        current = (int *)current[5]; // next pointer is at offset +0x14 (5 words)
        if (current == nullptr) {
            return 1; // not found
        }
    }

    // Node found, unlink it from hash bucket
    if (prev != nullptr) {
        // Node is not the first in the bucket
        prev[5] = current[5];
    } else {
        // Node is the first in the bucket, update bucket head
        bucketArray[hash] = (int *)current[5];
    }

    // Add node to free list (head at offset +0x0C)
    int freeListHead = *(int *)(this_int + 0x0C);                    // +0x0C: free list head
    current[5] = freeListHead;
    *(int *)(this_int + 0x0C) = (int)current;

    // Decrement active node count (offset +0x10)
    int activeCount = *(int *)(this_int + 0x10);                     // +0x10: active node count
    *(int *)(this_int + 0x10) = activeCount - 1;

    return 0; // success
}