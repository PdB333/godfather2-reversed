// FUNC_NAME: heapAlloc
// Allocation size = (param1 * 8) + 16, aligned to 16 bytes
// Returns pointer to allocated block, or NULL if out of memory

void* heapAlloc(int size) {
    uint alignedSize;
    int currentBlockEnd;
    undefined8* currentAllocPtr;
    undefined8* newBlock;
    undefined4* freeNode;
    undefined4* freeNodePrev;
    uint uVar7;
    undefined4* nextFree;
    
    int heapBase = DAT_0120555c;                      // Global heap descriptor (likely HeapControlBlock)
    alignedSize = (size * 8 + 0x10);                   // Actual block size = 16 + size*8 (maybe footprint)
    if ((alignedSize & 0xf) != 0) {                     // Align up to 16 bytes
        alignedSize += 0x10 - (alignedSize & 0xf);
    }
    
    currentAllocPtr = *(undefined8**)(heapBase + 8);   // +0x8: pointer to current allocation area
    uint newTop = (uint)currentAllocPtr + alignedSize; // Next allocation would go here
    
    // Check if there's room in the current monolithic block
    // heapBase+0x10: block end address? heapBase+0xc: something (maybe block size)
    currentBlockEnd = *(int*)(heapBase + 0x10) + *(int*)(heapBase + 0xc);
    if ((uint)currentBlockEnd < newTop) {
        // Not enough space in current block – search free list
        freeNodePrev = (undefined4*)**(undefined4**)(heapBase + 4); // +0x4: pointer to first free node? Actually double deref?
        freeNode = *(undefined4**)(heapBase + 4);                    // Current free node pointer
        while (true) {
            nextFree = freeNodePrev;                    // Save previous node
            currentAllocPtr = *(undefined8**)(heapBase + 0xc); // Re-read? Actually used as base of free block area
            if (nextFree != (undefined4*)0x0) {
                // Node is valid; compute its data start: node + (short from offset 10)
                currentAllocPtr = (undefined8*)((uint)*(ushort*)((int)nextFree + 10) + (int)nextFree);
            }
            // Check if this free block has enough contiguous space
            if (alignedSize <= (uint)((int)freeNode - (int)currentAllocPtr)) break;
            if (nextFree == (undefined4*)0x0) {
                return (void*)0x0;                      // No suitable free block found
            }
            freeNodePrev = (undefined4*)*nextFree;     // Move to next node in list
            freeNode = nextFree;
        }
        // Found a suitable free block: allocate from it
        if (currentAllocPtr == (undefined8*)0x0) {
            newBlock = (undefined8*)0x0;
        }
        else {
            *currentAllocPtr = 0;                       // Clear first two qwords (header)
            currentAllocPtr[1] = 0;
            newBlock = currentAllocPtr;
        }
        *(short*)((int)newBlock + 10) = (short)alignedSize; // +0x10: block size
        *(undefined4**)newBlock = nextFree;              // +0x00: next pointer (links to previous free node)
        *(undefined4**)((int)newBlock + 4) = freeNode;  // +0x04: prev pointer
        *(undefined1*)(newBlock + 1) = 0;               // +0x08: some flag? (low byte of third qword)
        *(undefined1*)((int)newBlock + 9) = 1;          // +0x09: used flag (1)
        *(int*)((int)newBlock + 0x0c) = size;           // +0x0c: original requested size?
        if (nextFree != (undefined4*)0x0) {
            nextFree[1] = (undefined4)currentAllocPtr;  // Update previous node's next pointer
        }
        *freeNode = (undefined4)newBlock;                // Update current node pointer
        return newBlock;
    }
    else {
        // Room in current block: allocate sequentially
        if (currentAllocPtr == (undefined8*)0x0) {
            newBlock = (undefined8*)0x0;
        }
        else {
            *currentAllocPtr = 0;                       // Clear header
            currentAllocPtr[1] = 0;
            newBlock = currentAllocPtr;
        }
        *(undefined4*)newBlock = *(undefined4*)(heapBase + 4); // Copy previous free pointer?
        *(undefined4*)((int)newBlock + 4) = 0;          // No previous?
        *(undefined1*)(newBlock + 1) = 0;
        *(undefined1*)((int)newBlock + 9) = 1;
        *(short*)((int)newBlock + 10) = (short)alignedSize;
        *(int*)((int)newBlock + 0x0c) = size;
        if (*(int*)(heapBase + 4) != 0) {
            *(undefined8**)(*(int*)(heapBase + 4) + 4) = newBlock; // Link back
        }
        *(uint*)(heapBase + 8) = newTop;                // Update current allocation pointer
        *(undefined8**)(heapBase + 4) = newBlock;       // Set as new head of free list?
        return newBlock;
    }
}