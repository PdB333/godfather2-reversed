// FUNC_NAME: NetConnection::getPacketSlotDataBySequence
uint32_t __thiscall NetConnection::getPacketSlotDataBySequence(int thisPtr, int sequenceNum) {
    // Calculate slot index from sequence number relative to base sequence
    // this+0x4 points to some state object, which contains base sequence at +0x4
    int baseSequence = *(int *)(*(int *)(thisPtr + 4) + 4);
    int slotIndex = sequenceNum - baseSequence;

    if (slotIndex < 0) {
        return 0xFFFFFFFF; // Invalid sequence number
    }

    // Determine the packet slot array base
    int* slotArrayBase;
    if (*(int *)(thisPtr + 0x1c) != 0) {
        // Use member pointer chain: this->somePtr->field10->field30 gives array base
        slotArrayBase = *(int **)(*(int *)(*(int *)(thisPtr + 0x1c) + 0x10) + 0x30);
    } else {
        // Use global array pointer (piRam00000030)
        slotArrayBase = (int *)*piRam00000030;
    }

    // Each slot is 0x70 bytes; retrieve slot pointer from array at offset 0x40
    int slotPtr = *(int *)(slotArrayBase + 0x40 + slotIndex * 0x70);
    // Return the value at offset +8 in the slot structure
    return *(uint32_t *)(slotPtr + 8);
}