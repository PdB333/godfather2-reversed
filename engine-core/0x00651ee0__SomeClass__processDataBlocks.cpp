// FUNC_NAME: SomeClass::processDataBlocks
void __thiscall SomeClass::processDataBlocks(int thisPtr, int blockSize, void *someData, uint dataLength, 
                                              void *extraParam1, void *extraParam2, int extraParam3, int freePtr, 
                                              int extraStackParam)
{
    int iterationPtr;
    int tempAllocPtr;
    int *tempAlloc;
    uint alignedLength;
    uint tempMasked;
    char tempBuffer[4];
    
    iterationPtr = (int)thisPtr;  // Use this as base pointer for iteration
    
    // Process data in chunks of blockSize*2 while there is enough remaining length
    while (blockSize * 2 <= (int)dataLength) {
        tempMasked = tempMasked & 0xffffff00;  // Align to 256-byte boundary
        int ptr1 = iterationPtr + blockSize * 4;      // offset 4*blockSize from current base
        int ptr2 = ptr1 + blockSize * 4;                // offset 8*blockSize
        iterationPtr = ptr1 + blockSize * 4;            // update iteration base for next chunk
        
        // Process three blocks at once (at offsets 0, blockSize*4, blockSize*8)
        processBlockTypeA(tempBuffer, 
                          (void*)iterationPtr,    // should be original iterationPtr? Note: logic uses param order
                          (void*)ptr1,
                          (void*)ptr1,            // duplicate parameter, likely same as ptr1
                          (void*)ptr2,
                          extraParam1,
                          dataLength,
                          tempMasked,
                          0, 0, 0, 0, 0,
                          extraStackParam);
        
        if (tempAlloc != (int *)0) {
            memoryFree(tempAlloc);
        }
        
        // Reduce remaining length by two blocks
        dataLength = dataLength + blockSize * (-2);
        
        // Update iteration pointer to current ptr2 (from the line above)
        iterationPtr = ptr2;
    }
    
    // If there is one partial block left (size between blockSize and blockSize*2)
    if (blockSize < (int)dataLength) {
        iterationPtr = iterationPtr + blockSize * 4;
        processBlockTypeB((void*)iterationPtr,  // Note: original passes iterationPtr? Actually in_EAX then...
                          (void*)iterationPtr,  // duplicate
                          (void*)iterationPtr,  // duplicate
                          someData,
                          extraParam1,
                          0, 0, 0, 0, 0,
                          extraStackParam);
    } else {
        // Less than one block remains: handle final alignment
        dataLength = dataLength & 0xffffff00;   // Align down to 256 bytes
        processBlockTypeC(tempBuffer, 
                          someData,
                          0, 0, 0, 0, 0,
                          extraStackParam,
                          dataLength,
                          dataLength,
                          dataLength);
    }
    
    // Free temporary allocations if they were used
    if (tempAlloc != (int *)0) {
        memoryFree(tempAlloc);
    }
    if (freePtr != 0) {
        memoryFree((void *)freePtr);
    }
}