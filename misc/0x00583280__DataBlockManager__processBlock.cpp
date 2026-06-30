// FUNC_NAME: DataBlockManager::processBlock

void __thiscall DataBlockManager::processBlock(uint param_2, uint param_3, uint flags) {
    // EAX contains a pointer to a context structure (type byte at +0, dest pointer at +4)
    // This is an implicit register parameter.

    if ((flags & 0x100) == 0) {
        // Alternate path: likely a different data block type
        this->alternateHandler(param_3);
        return;
    }

    // Source: pointer stored at this+4 (e.g., an embedded data array)
    uint32_t* sourceArray = *(uint32_t**)((uint8_t*)this + 4);

    // Destination: pointer stored at context+4
    uint32_t* destArray = *(uint32_t**)((uint8_t*)_in_EAX + 4);

    // Mark context type as 2 (e.g., "received block ready")
    *(uint8_t*)_in_EAX = 2;

    // Copy 8 dwords (32 bytes) from source to destination
    destArray[0] = sourceArray[0];
    destArray[1] = sourceArray[1];
    destArray[2] = sourceArray[2];
    destArray[3] = sourceArray[3];
    destArray[4] = sourceArray[4];
    destArray[5] = sourceArray[5];
    destArray[6] = sourceArray[6];
    destArray[7] = sourceArray[7];
}