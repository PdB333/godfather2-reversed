// FUNC_NAME: ObjectHashTable::findByHash
// Function at 0x00446290 - Searches for an object by a 32-bit hash computed from a four-integer identifier.
// Uses a linked list and an optional bucket array for chaining.
int __thiscall ObjectHashTable::findByHash(void* this, int hash) {
    // Get the head of the global linked list of all objects.
    int* currentNode = (int*)getHead(); // FUN_00448be0 - returns first node
    if (currentNode == 0) {
        return 0; // Empty list, not found.
    }

    // Access the bucket array if present (offset +0x70 = bucket pointer, +0x74 = count)
    bool hasBuckets = (*(int**)((char*)this + 0x70) != 0);
    unsigned int bucketIndex = 0;
    int** bucketArray = 0;
    unsigned int bucketCount = 0;
    if (hasBuckets) {
        bucketArray = *(int***)((char*)this + 0x70);
        bucketCount = *(unsigned int*)((char*)this + 0x74);
    }

    while (true) {
        // If we've exhausted the current chain, fetch the next non-empty bucket.
        while (currentNode == 0) {
            if (!hasBuckets) {
                return 0; // No more buckets – not found.
            }
            if (bucketIndex >= bucketCount) {
                return 0; // All buckets scanned – not found.
            }
            currentNode = bucketArray[bucketIndex];
            bucketIndex++;
        }

        // Retrieve the four-integer hash data from the current node.
        // FUN_0043ab10 returns a pointer to the struct containing the hash components.
        int* hashData = (int*)getHashData(currentNode); // Assumed to take the node as implicit 'this'
        int computedHash = ((hashData[0] * 0x21 + hashData[1]) * 0x21 + hashData[2]) * 0x21 + hashData[3];

        if (hash == computedHash) {
            return (int)currentNode; // Found matching node.
        }

        // Move to the next node in the current chain (offset +0x18 is the next pointer).
        currentNode = (int*)*(int*)((char*)currentNode + 0x18);
    }
}