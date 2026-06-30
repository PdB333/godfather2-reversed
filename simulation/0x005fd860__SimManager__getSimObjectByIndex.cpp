// FUNC_NAME: SimManager::getSimObjectByIndex
// 0x005fd860 - Retrieves a sim object pointer and value from internal table (entries at this+0x70, stride 0xC)
// param_2: pointer to index (int*)
// param_3: output pointer to retrieved object (int*)
// param_4: output value associated with the object (undefined4*)
// Returns: 0 if not found, else (second_field>>8) | 0x01000000 (handle with flag)
int __thiscall SimManager::getSimObjectByIndex(int thisPtr, int* pIndex, int* outObjectPtr, uint32_t* outValue)
{
    int idx = *pIndex;  // Read index from caller-provided pointer
    // Array of entries starts at offset 0x70; each entry is 12 bytes (0xC)
    // First field (offset +0x0 within entry): object pointer
    int objPtr = *(int*)(thisPtr + 0x70 + idx * 0xC);
    *outObjectPtr = objPtr;

    if (objPtr != 0) {
        // Second field (offset +0x8 within entry): additional data (e.g., handle, generation)
        uint32_t data = *(uint32_t*)(thisPtr + idx * 0xC + 0x78);
        *outValue = data;
        // Build combined return: low byte = 1 (success flag), high 24 bits = shifted data
        return ((data >> 8) & 0x00FFFFFF) | 0x01000000;
    }

    *outValue = 0;
    return 0;
}