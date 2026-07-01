// FUNC_NAME: Animation::findNextLinkedLayer
int __thiscall Animation::findNextLinkedLayer(int thisPtr, int currentSlotIndex) {
    uint* slotFlagsPtr;
    int slotIter;
    
    // Guard against invalid index
    if (currentSlotIndex == -1) {
        return -1;
    }
    
    // Check if the current slot has the "linked" flag (bit 1) set
    slotFlagsPtr = (uint*)(thisPtr + 0x18 + currentSlotIndex * 0x24);
    if ((*slotFlagsPtr >> 1 & 1) == 0) {
        // Not a linked slot, nothing to find
        return -1;
    }
    
    // Iterate over all 7 slots
    slotIter = 0;
    slotFlagsPtr = (uint*)(thisPtr + 0x18);  // Base of slot array
    while (slotIter < 7) {
        // Check if the iterated slot is active (bit0 set) and not a link (bit1 clear)
        if (((*slotFlagsPtr & 1) != 0) && ((*slotFlagsPtr >> 1 & 1) == 0)) {
            // The second word of the iterated slot (+0x04) must equal 
            // the linkedId stored in the current slot (+0x1c) + 1
            if (slotFlagsPtr[1] == *(int*)(thisPtr + currentSlotIndex * 0x24 + 0x1c) + 1) {
                return slotIter;
            }
        }
        slotIter++;
        slotFlagsPtr += 9;  // Advance to next slot (9 uint32s = 0x24 bytes)
    }
    
    // No matching slot found
    return -1;
}