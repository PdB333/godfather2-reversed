// FUNC_NAME: HashTable::clear
void __thiscall HashTable::clear(void)
{
    int *bucketPtr;
    int bucketIndex;
    int node;
    int nextNode;
    int *freeNode;
    int *pendingFreeNode;

    // Clear all buckets (0x400 = 1024 buckets)
    bucketPtr = (int *)(this + 0x30);
    bucketIndex = 0x400;
    do {
        node = *bucketPtr;
        if (node != 0) {
            // Traverse the linked list in this bucket
            nextNode = *(int *)(node + 0x30);
            *(int *)(node + 0x30) = 0;
            *(int *)(node + 0x34) = 0;
            while (nextNode != 0) {
                node = nextNode;
                nextNode = *(int *)(node + 0x30);
                *(int *)(node + 0x30) = 0;
                *(int *)(node + 0x34) = 0;
            }
        }
        *bucketPtr = 0;
        bucketPtr++;
        bucketIndex--;
    } while (bucketIndex != 0);

    // Move all nodes from the pending free list to the main free list
    pendingFreeNode = *(int **)(this + 0x14);
    while (pendingFreeNode != (int *)0x0) {
        freeNode = (int *)*pendingFreeNode;
        pendingFreeNode[1] = 0; // Clear some field at +0x04
        *pendingFreeNode = *(int *)(this + 0x10); // Link to current free list head
        *(int *)(*(int *)(this + 0x10) + 4) = (int)pendingFreeNode; // Update previous head's back pointer? Actually +4 is set to pendingFreeNode
        *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + 1; // Increment free count
        *(int **)(this + 0x10) = pendingFreeNode; // Update free list head
        pendingFreeNode = freeNode;
    }

    // Reset various counters and pointers
    *(int *)(this + 0x18) = 0; // Some count
    *(int *)(this + 0x14) = 0; // Pending free list head
    *(int *)(this + 0x2c) = 0; // Unknown
    *(int *)(this + 0x28) = 0; // Unknown
    *(int *)(this + 0x1040) = 0; // Large offset fields (maybe stats or other arrays)
    *(int *)(this + 0x103c) = 0;
    *(int *)(this + 0x1038) = 0;
    *(int *)(this + 0x1034) = 0;
    *(int *)(this + 0x1030) = 0;
    return;
}