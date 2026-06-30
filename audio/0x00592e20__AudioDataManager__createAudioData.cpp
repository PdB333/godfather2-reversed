// FUNC_NAME: AudioDataManager::createAudioData
int __cdecl AudioDataManager::createAudioData(uint param1, uint param2, uint param3, uint eaxParam)
{
    uint tempData[8]; // 32-byte structure, initialized to zero and then partially set
    int allocatedPtr;

    // Initialize tempData to zero, then set specific fields
    tempData[0] = 0; // +0x00
    tempData[1] = 0; // +0x04
    tempData[2] = 0; // +0x08
    tempData[3] = DAT_00e2b1a4; // +0x0C, likely some constant (e.g., flag or float)
    tempData[4] = 0; // +0x10
    tempData[5] = 0; // +0x14
    tempData[6] = 0; // +0x18
    tempData[7] = DAT_00e2b1a4; // +0x1C, same constant

    // Initialize the data block using the provided parameters
    // This likely validates/fills the structure
    if (FUN_00592ec0(tempData, param1, eaxParam, param2, param3) == 0) {
        return 0; // Initialization failed
    }

    // Allocate a new object (probably with some internal allocator)
    allocatedPtr = FUN_005931a0();
    if (allocatedPtr != 0) {
        // Copy the 32-byte data block into the allocated object at offset +0x10
        *(uint *)(allocatedPtr + 0x10) = tempData[0];
        *(uint *)(allocatedPtr + 0x14) = tempData[1];
        *(uint *)(allocatedPtr + 0x18) = tempData[2];
        *(uint *)(allocatedPtr + 0x1C) = tempData[3];
        *(uint *)(allocatedPtr + 0x20) = tempData[4];
        *(uint *)(allocatedPtr + 0x24) = tempData[5];
        *(uint *)(allocatedPtr + 0x28) = tempData[6];
        *(uint *)(allocatedPtr + 0x2C) = tempData[7];
        return allocatedPtr;
    }

    return 0; // Allocation failed
}