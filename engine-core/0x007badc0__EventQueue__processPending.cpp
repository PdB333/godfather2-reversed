// FUNC_NAME: EventQueue::processPending
uint __thiscall EventQueue::processPending(int thisPtr, uint identifier, void* object) {
    char checkResult;
    int count;
    int headIdx;
    int maxSize;
    int* buffer;
    uint someFlag;
    int tempIdx;

    // Check if identifier is valid or pending? FUN_0079e920 likely returns a boolean
    checkResult = someValidationFunction(identifier);
    if (checkResult == 0) {
        // Mark object as pending (offset 0x7d + thisPtr)
        *(byte*)((int)object + 0x7d + thisPtr) = 1;
    } else if (*(byte*)((int)object + 0x7d + thisPtr) != 0) {
        // Object is pending, try to enqueue
        count = *(int*)(thisPtr + 0x8c);
        maxSize = *(int*)(thisPtr + 0x84);
        if (count < maxSize) {
            // Calculate write position
            buffer = *(int**)(thisPtr + 0x80);
            headIdx = *(int*)(thisPtr + 0x88);
            tempIdx = headIdx + count;
            if (tempIdx >= maxSize) {
                tempIdx -= maxSize;
            }
            *(int*)(thisPtr + 0x8c) = count + 1;
            buffer[tempIdx] = (int)object;
        }
        // Clear pending flag
        *(byte*)((int)object + 0x7d + thisPtr) = 0;
    }

    someFlag = checkGlobalPendingFlag(); // FUN_007ba5a0, likely returns some global status
    if (((byte)someFlag != 0) && (*(int*)(thisPtr + 0x8c) != 0)) {
        // Check if this object is at the front of the queue
        headIdx = *(int*)(thisPtr + 0x88);
        buffer = *(int**)(thisPtr + 0x80);
        if (buffer[headIdx] == (int)object) {
            // Dequeue front
            headIdx++;
            if (headIdx >= *(int*)(thisPtr + 0x84)) {
                headIdx = 0;
            }
            *(int*)(thisPtr + 0x88) = headIdx;
            *(int*)(thisPtr + 0x8c) = *(int*)(thisPtr + 0x8c) - 1;
            // Return value: low byte = 1, higher bytes = new head index >> 8
            return (headIdx >> 8) << 8 | 1;
        }
    }
    // Return the global flag with low byte cleared
    return someFlag & 0xFFFFFF00;
}