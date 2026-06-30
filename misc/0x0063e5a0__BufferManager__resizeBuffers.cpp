// FUNC_NAME: BufferManager::resizeBuffers
void __thiscall BufferManager::resizeBuffers(void) {
    int *descriptor = *(int **)(this + 0x1c); // pointer to a descriptor struct (stack of resize requests)
    int *targetBufferSet = *descriptor;       // pointer to the buffer set being updated (iVar2)

    lock(); // FUN_0063df30 - critical section lock (maybe)
    debugLog(0x801b, descriptor[3] + 8);      // FUN_006438e0 - log/event

    // Resize array1: element size 4 (int32)
    targetBufferSet->array1Ptr = (int*)reallocateBuffer(
        targetBufferSet->array1Count * 4,
        descriptor[6] * 4);
    targetBufferSet->array1Count = descriptor[6];

    // Resize array2: element size 4 (int32)
    targetBufferSet->array2Ptr = (int*)reallocateBuffer(
        targetBufferSet->array2Count * 4,
        descriptor[6] * 4);
    targetBufferSet->array2Count = descriptor[6];

    // Resize array3: element size 8 (probably two ints or a struct)
    targetBufferSet->array3Ptr = (void*)reallocateBuffer(
        targetBufferSet->array3Count * 8,
        descriptor[10] * 8);
    targetBufferSet->array3Count = descriptor[10];

    // Resize array4: element size 4 (int32)
    targetBufferSet->array4Ptr = (int*)reallocateBuffer(
        targetBufferSet->array4Count * 4,
        descriptor[0xb] * 4);
    targetBufferSet->array4Count = descriptor[0xb];

    // Resize array5: element size 12 (e.g., 3 ints)
    targetBufferSet->array5Ptr = (void*)reallocateBuffer(
        targetBufferSet->array5Count * 12,
        descriptor[0xc] * 12);
    targetBufferSet->array5Count = descriptor[0xc];

    // Resize array6: element size 4, new count from byte field at +0x44
    uint newCount6 = *(byte *)(targetBufferSet + 0x44);
    targetBufferSet->array6Ptr = (int*)reallocateBuffer(
        targetBufferSet->array6Count * 4,
        newCount6 * 4);
    targetBufferSet->array6Count = newCount6;

    // Move to next descriptor in the stack/linked list
    *(int **)(this + 0x1c) = (int *)descriptor[2]; // pop descriptor
    return;
}