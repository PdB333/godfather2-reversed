// FUNC_NAME: ArrayContainer::push_back
undefined4 __thiscall ArrayContainer::push_back(int thisPtr, int elementPtr)
{
    undefined4 handle;
    int currentCount;
    int capacity;
    undefined8 *destSlot;

    // Acquire some reference or handle from global manager
    handle = acquireHandle(); // FUN_0049c9c0

    // Attach handle to element's field at offset +0x18 (likely a reference count or ID)
    setElementHandle(handle, *(int *)(elementPtr + 0x18)); // FUN_00604d80

    currentCount = *(int *)(thisPtr + 0x10); // +0x10: current element count
    capacity = *(int *)(thisPtr + 0x14);    // +0x14: current capacity

    if (currentCount == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // Reallocate internal array to new capacity
        reallocateArray(capacity); // FUN_00816760
    }

    // Calculate destination slot: base pointer + (count * 0x10)
    destSlot = (undefined8 *)(*(int *)(thisPtr + 0xc) + (currentCount * 0x10));
    // Increment count
    *(int *)(thisPtr + 0x10) = currentCount + 1;

    // Copy 16-byte element into slot
    if (destSlot != (undefined8 *)0x0) {
        *destSlot = local_10;   // undefined8 local_10, undefined8 local_8
        destSlot[1] = local_8;  // from stack; likely copy of element data
    }

    // Release or finalize handle
    releaseHandle(); // FUN_00604da0

    return handle;
}