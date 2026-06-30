// FUNC_NAME: TNLConnection::allocateReliableSendSlot
int TNLConnection::allocateReliableSendSlot() {
    int slotCount = this->slotCount;          // +0x00: number of slots in the window (e.g., 28)
    int bitLength;
    if (slotCount == 0) {
        bitLength = 0;
    } else {
        bitLength = (slotCount - 1) * 0x1c;   // base offset for bit counting
        // Get the free/pending bitmask for the last slot (index slotCount-1)
        uint32_t mask = *(uint32_t *)(this->slotBitmaskArray + (slotCount - 1) * 4); // +0x0C points to uint32 array
        while (mask != 0) {
            bitLength++;
            mask >>= 1;                       // count bits until mask becomes zero
        }
    }

    // Compute the starting index for allocation: wrap modulo 0x1c, then normalize
    int startIdx = (bitLength % 0x1c) - 0x1d + slotCount * 0x1c;
    int slot = FUN_00665720(startIdx);        // attempt to claim a slot at this index
    if (slot == 0) {
        // Linear probe: try each of the 28 sub-slots starting from (bitLength%28)-1
        for (int i = (bitLength % 0x1c) - 1; i < 0x1c; i++) {
            int result = FUN_00668da0();      // maybe check if slot i is available
            if (result != 0) {
                return result;
            }
            result = FUN_00665c30();          // maybe update some state
            if (result != -1) {
                result = FUN_0066c8d0();      // finalize slot allocation
                if (result != 0) {
                    return result;
                }
            }
        }
        slot = 0;                             // failed to allocate
    }
    return slot;
}