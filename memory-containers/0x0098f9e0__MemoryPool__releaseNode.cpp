// FUNC_NAME: MemoryPool::releaseNode
void __fastcall MemoryPool::releaseNode(int this)
{
    int index = getFreeIndex(); // FUN_0098f3f0 - returns an index from a free list
    if (index < 0) {
        return;
    }

    // Decrement total node count at +0x48
    *(int *)(this + 0x48) = *(int *)(this + 0x48) - *(int *)(*(int *)(*(int *)(this + 0x3c) + 4 + index * 8) + 8);
    // Note: The subtraction uses a value from the node's structure at offset +0x8? Actually the expression is complex:
    // *(int *)(*(int *)(*(int *)(this+0x3c) + 4 + index*8) + 8)
    // This reads the node pointer from the array, then reads offset +0x8 from that node.
    // So each node has a "size" or "weight" at +0x8.

    if (*(int *)(this + 0x48) < *(int *)(this + 0x4c)) {
        // If total count falls below threshold, adjust threshold
        *(int *)(this + 0x4c) = *(int *)(this + 0x48) - 1;
    }

    // Get the node pointer from the array entry
    int* nodePtr = *(int**)(*(int *)(this + 0x3c) + 4 + index * 8); // puVar1

    // If node has a destructor callback (offset +0x10 non-zero), call it
    if (*(int*)(nodePtr + 4) != 0) { // nodePtr[4] is offset 0x10
        (*(void (__stdcall **)(int))(nodePtr + 7))(*(int*)(nodePtr + 4)); // nodePtr[7] is offset 0x1c, argument is nodePtr[4]
    }

    // Link node into free list: node->nextFree = freeListHead
    *nodePtr = *(int *)(this + 0x38); // freeListHead

    // Update counts
    *(int *)(this + 0x14) = *(int *)(this + 0x14) - 1; // freeCount--
    *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1; // allocatedCount++? Actually this seems reversed: freeCount decreases, allocatedCount increases? But we are releasing a node, so allocated should decrease. Possibly the names are swapped. We'll keep as is.

    // Set free list head to this node
    *(int**)(this + 0x38) = nodePtr;

    // Mark the index as free in the index manager
    markIndexFree(index); // FUN_0098f480
}