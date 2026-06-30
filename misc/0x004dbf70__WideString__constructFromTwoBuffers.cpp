// FUNC_NAME: WideString::constructFromTwoBuffers
void __thiscall WideString::constructFromTwoBuffers(int *thisPtr, void *src1, uint len1, void *src2, uint len2)
{
    uint totalLen;
    void *allocatedData;

    if (len1 != 0) {
        if (len2 == 0) {
            // Only first buffer provided
            thisPtr[1] = len1;                        // +0x04: length (characters)
            thisPtr[2] = len1 * 2;                    // +0x08: capacity (bytes)
            allocatedData = heapAllocate((len1 + 1) * 2);
            thisPtr[0] = (int)allocatedData;          // +0x00: data pointer
            memcpy(allocatedData, src1, len1 * 2);
        } else {
            // Both buffers provided — concatenate
            totalLen = len1 + len2;
            thisPtr[1] = totalLen;
            thisPtr[2] = totalLen * 2;
            allocatedData = heapAllocate((totalLen + 1) * 2);
            thisPtr[0] = (int)allocatedData;
            memcpy(allocatedData, src1, len1 * 2);
            memcpy((void *)(thisPtr[0] + len1 * 2), src2, len2 * 2);
        }
        // Null-terminate (2-byte null)
        *(short *)(thisPtr[0] + thisPtr[1] * 2) = 0;
        thisPtr[3] = (int)thunk_FUN_009c8eb0;        // +0x0C: custom deleter
        return;
    }

    // First buffer is empty
    if (len2 != 0) {
        // Only second buffer provided
        thisPtr[1] = len2;
        thisPtr[2] = len2 * 2;
        allocatedData = heapAllocate((len2 + 1) * 2);
        thisPtr[0] = (int)allocatedData;
        memcpy(allocatedData, src2, len2 * 2);
        *(short *)(thisPtr[0] + thisPtr[1] * 2) = 0;
        thisPtr[3] = (int)thunk_FUN_009c8eb0;
        return;
    }

    // Both buffers empty — set as empty string
    thisPtr[0] = 0;
    thisPtr[2] = 0;
    thisPtr[1] = 0;
}