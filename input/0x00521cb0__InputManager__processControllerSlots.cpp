// FUNC_NAME: InputManager::processControllerSlots
uint __fastcall InputManager::processControllerSlots(void* thisPtr, int dataSize1, int dataSize2, void* outputBuffer, int* outputCount) {
    // thisPtr points to controller state structure (44 bytes? Actually 11 dwords)
    uint local_counter; // loop counter
    int local_count; // variable counts
    int local_temp[4]; // part of buffer, but actually used as base for pointer arithmetic
    undefined4 stack_2ac, stack_2a8, stack_2a4;
    undefined4 largeBuffer[167]; // 668 bytes buffer for intermediate storage

    // Copy first 12 bytes from input structure (controller state fields)
    local_temp[3] = *(int*)thisPtr;
    stack_2ac = ((int*)thisPtr)[1];
    stack_2a8 = ((int*)thisPtr)[2];
    largeBuffer[0] = ((int*)thisPtr)[4];
    largeBuffer[1] = ((int*)thisPtr)[5];
    largeBuffer[2] = ((int*)thisPtr)[6];
    largeBuffer[4] = ((int*)thisPtr)[8];
    largeBuffer[5] = ((int*)thisPtr)[9];
    largeBuffer[6] = ((int*)thisPtr)[10];
    // Note: indices 3 and 7 are zeroed/initialized later

    local_temp[0] = 3;              // +0x00: some counter
    local_temp[1] = 0;              // +0x04: flag?
    largeBuffer[7] = DAT_00e2b1a4;  // global constant, maybe -1 or 0?
    largeBuffer[3] = DAT_00e2b1a4;
    stack_2a4 = DAT_00e2b1a4;       // +0x08: seems unused directly? Actually used in copy loop
    local_counter = 0;

    local_temp[2] = dataSize1 - dataSize2; // +0x08: difference of sizes

    do {
        uint temp = local_counter & 0x80000001; // keep sign bit and bit0
        if ((int)temp < 0) {
            temp = (temp - 1 | 0xfffffffe) + 1;
        }
        // temp is now (local_counter & 1) but with sign handling? Actually it's always 0 or 1.
        local_temp[1 - temp] = 0; // clear one of the two alternating buffers

        // Call processing function with alternating buffer addresses
        uint result = FUN_00521dd0(&local_temp[temp * 0x54 / 4 + 3],  // +3 offset = 12 bytes
                                  local_temp[temp],
                                  dataSize2,
                                  &local_temp[(1 - temp) * 0x54 / 4 + 3]);
        if ((char)result == '\0') goto FAIL;
        local_counter++;
        dataSize2 += 16; // advance by 16 bytes each iteration
    } while ((int)local_counter < 6);

    if (local_temp[0] > 2) {
        int inputIndex = *outputCount; // starting index from caller
        int byteOffset = inputIndex << 4; // each output entry is 16 bytes? Actually *16 then +0x30 steps
        undefined4* srcPtr = largeBuffer;
        local_temp[0] -= 2; // adjust count

        do {
            // Copy 4 dwords from source buffer (first 16 bytes)
            srcPtr += 4;
            undefined4 v0 = srcPtr[-4];
            undefined4 v1 = srcPtr[-3];
            undefined4 v2 = srcPtr[-2];
            undefined4 v3 = srcPtr[-1];
            // Write to output at position (byteOffset) and (byteOffset+0x10)
            int* dst1 = (int*)(byteOffset + (int)outputBuffer);
            dst1[0] = local_temp[3];
            dst1[1] = stack_2ac;
            dst1[2] = stack_2a8;
            dst1[3] = stack_2a4;
            int* dst2 = (int*)(byteOffset + 0x10 + (int)outputBuffer);
            dst2[0] = v0;
            dst2[1] = v1;
            dst2[2] = v2;
            dst2[3] = v3;
            // Get next 4 dwords
            undefined4 u1 = srcPtr[1];
            undefined4 u2 = srcPtr[2];
            undefined4 u3 = srcPtr[3];
            // Write third block at byteOffset+0x20
            int* dst3 = (int*)(byteOffset + 0x20 + (int)outputBuffer);
            inputIndex += 3;
            byteOffset += 0x30; // advance 48 bytes (3 * 16)
            local_temp[0]--;
            dst3[0] = *srcPtr;
            dst3[1] = u1;
            dst3[2] = u2;
            dst3[3] = u3;
        } while (local_temp[0] != 0);
        *outputCount = inputIndex; // update output count
        return 0x100; // success flag (low byte = 1, high bytes zero)
    }
FAIL:
    return result & 0xffffff00; // failure, return only high byte? Actually mask off low byte
}