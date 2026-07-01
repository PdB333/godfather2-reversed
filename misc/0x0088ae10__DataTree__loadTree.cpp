// FUNC_NAME: DataTree::loadTree
void __thiscall DataTree::loadTree(int this, int* treeData, int depth)
{
    uint hashKey;
    bool shouldAllocate;
    uint** bucketPtr;
    uint* currentNode;
    int allocatedPtr;
    uint nodeCount;
    uint hashValue;
    uint bucketCount;
    uint* bucketList;
    uint local_24;
    uint* local_18;
    uint* local_10;
    uint* local_c;

    // Compute node count from two bytes: (treeData[0]+10) bit0 + treeData[0]+8
    nodeCount = (*(byte*)(*treeData + 10) & 1) + (uint)*(byte*)(*treeData + 8);
    local_24 = 0;
    bucketCount = g_hashTableSize;          // DAT_00e54200
    bucketList = g_hashTableBuckets;        // PTR_DAT_00e541fc
    if (nodeCount != 0) {
        do {
            // Get the hash key for this node
            hashKey = **(uint**)(*(int*)(*treeData + 0x10) + local_24 * 4);
            // Compute hash bucket index
            hashValue = hashKey % bucketCount;
            // Search bucket chain for this key
            for (currentNode = *(uint**)(bucketList + hashValue * 4); 
                 currentNode != (uint*)0x0;
                 currentNode = (uint*)currentNode[7]) {  // next pointer at offset 28
                if (hashKey == *currentNode) {
                    local_18 = currentNode;
                    // Set up pointer to the bucket head
                    local_14 = bucketList + hashValue * 4;
                    bucketPtr = &local_18;
                    goto LAB_0088ae91;
                }
            }
            // Key not found: use the bucket head itself
            local_c = bucketList + bucketCount * 4;  // sentinel? bucketCount*4 is beyond bucket list
            local_10 = *(uint**)(bucketList + bucketCount * 4);
            bucketPtr = &local_10;
LAB_0088ae91:
            // If the selected node is not the sentinel and has a valid next pointer
            if ((*bucketPtr != *(uint**)(bucketList + bucketCount * 4)) &&
                (currentNode = *bucketPtr + 1, currentNode != (uint*)0x0)) {
                // Recurse into child tree (depth+1)
                loadTree(currentNode, depth + 1);
                // Reload globals (they might be modified by recursion)
                bucketCount = g_hashTableSize;
                bucketList = g_hashTableBuckets;
            }
            local_24 = local_24 + 1;
        } while (local_24 < nodeCount);
    }

    // Determine if we should allocate a new object at this depth
    shouldAllocate = false;
    if (((*(byte*)(treeData + 4) & 1) != 0) || (*(short*)((int)treeData + 0x12) == 0)) {
        shouldAllocate = true;
    }
    // Increment depth counter (offset 0x12)
    *(short*)((int)treeData + 0x12) = *(short*)((int)treeData + 0x12) + 1;

    if (shouldAllocate) {
        // Allocate memory: size = depth * 8? (float depth is multiplied by 8)
        allocatedPtr = AllocateMemory(**(undefined4**)*treeData, (float)depth, 8);
        treeData[1] = allocatedPtr;

        // Copy to this object's field at +0x3c, or to null if no this
        if (this != 0) {
            CopyMemory(allocatedPtr, 4, this + 0x3c);
            return;
        }
        CopyMemory(allocatedPtr, 4, 0);
    }
    return;
}