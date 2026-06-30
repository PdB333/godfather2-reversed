// FUNC_NAME: HashTable::remove
// Address: 0x004218d0
// Description: Removes a node from a global hash table. The node is identified by a key at offset +0x1c.
// The hash table is a simple array-of-linked-lists structure.
// The global structure is at address 0x012053ac, containing:
//   [0] = bucket array base (pointer to int)
//   [1] = number of buckets (int)
//   [2] = total element count (int)
// Each node has:
//   +0x00: (other fields, not used here)
//   +0x1c: key (hash input)
//   +0x2c: next pointer
// Returns 0 on success, 1 if node not found.

int __thiscall HashTable::remove(void) {
    int *tableBase = (int *)DAT_012053ac;          // Global hash table descriptor
    int *bucketArray = (int *)tableBase[0];
    int bucketCount = tableBase[1];
    int *currentCount = (int *)&tableBase[2];

    // Compute hash from this->key (offset 0x1c)
    uint hash = FUN_004209c0(*(int *)((int)this + 0x1c));   // Call hash function
    uint bucketIndex = hash % bucketCount;

    int *curr = (int *)bucketArray[bucketIndex];
    int *prev = NULL;

    while (curr != NULL) {
        if (curr == this) {
            if (prev != NULL) {
                // Remove from middle or end: link previous to current->next
                prev[0x0b] = curr[0x0b];   // offset 0x2c = 11 ints? Actually 0x2c/4 = 11, but we treat as int*
                // More precisely: *(int **)(prev + 0x2c) = *(int **)(curr + 0x2c);
            } else {
                // Remove from bucket head: update bucket pointer
                bucketArray[bucketIndex] = curr[0x0b];   // curr->next
            }
            (*currentCount)--;
            return 0;
        }
        prev = curr;
        curr = (int *)curr[0x0b];   // curr->next at offset 0x2c
    }
    return 1;   // Node not found
}