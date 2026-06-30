// FUNC_NAME: HashTable::removeNode
// Function at 0x00616ed0: Removes a node from a hash table bucket chain.
// The hash table has 512 buckets (0x200) and stores count at +0x800.
// Each node has: +0x04 hash key, +0x08 next pointer.
int __thiscall HashTable::removeNode(int thisPtr, int nodePtr)
{
    uint hashIndex;
    int bucketHead;
    int prevNode;
    int currNode;
    int result;

    // Extract hash key from node and mask to 9 bits (0-511)
    hashIndex = *(uint *)(nodePtr + 4) & 0x1ff;
    // Get first node in the bucket
    bucketHead = *(int *)(thisPtr + hashIndex * 4);
    result = 1;
    prevNode = 0;

    if (bucketHead != 0) {
        // Walk the bucket chain to find the matching node
        for (currNode = bucketHead; currNode != nodePtr; currNode = *(int *)(currNode + 8)) {
            prevNode = currNode;
            if (*(int *)(currNode + 8) == 0) {
                // Reached end of chain without finding node - return failure
                return result;
            }
        }

        // Found the node - unlink it from chain
        if (prevNode != 0) {
            // Node is not the bucket head - update previous node's next pointer
            *(int *)(prevNode + 8) = *(int *)(currNode + 8);
            // Decrement total count (+0x800)
            *(int *)(thisPtr + 0x800) = *(int *)(thisPtr + 0x800) - 1;
            return 0;
        }

        // Node is the bucket head - update bucket pointer directly
        *(int *)(thisPtr + hashIndex * 4) = *(int *)(currNode + 8);
        *(int *)(thisPtr + 0x800) = *(int *)(thisPtr + 0x800) - 1;
        result = 0;
    }

    return result;
}