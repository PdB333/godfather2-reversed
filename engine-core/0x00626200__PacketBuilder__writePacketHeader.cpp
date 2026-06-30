// FUNC_NAME: PacketBuilder::writePacketHeader

void __thiscall PacketBuilder::writePacketHeader(int param_2, int param_3, undefined4 param_4) {
    // param_2: slot index (debug assertion: must be >= 0)
    // param_3: number of 8-byte data units to reserve before the header
    // param_4: unused (possibly reserved for future use)

    // Debug check: if slot index is negative, trigger assertion
    if ((param_2 != 0) && (param_2 < 1)) {
        FUN_00625430(); // likely Debug::assertFailed
    }

    // Compute new write pointer by moving backward from current buffer position
    // +0x8: pointer to current write position in the send buffer
    int newWritePtr = *(int *)(this + 0x8) - (param_3 * 8 + 8);

    // Store the unused param_4 locally (probably a future alignment or flag)
    undefined4 local_c = param_4;

    // Copy a fixed packet header template from static memory to the reserved space
    // &newWritePtr is actually the destination address (the value of newWritePtr, not its stack address)
    // FUN_00636570: likely a memcpy / buffer copy function
    // Size = newWritePtr - *(int *)(this + 0x1c) (difference from the base buffer pointer)
    FUN_00636570(&LAB_006261e0, &newWritePtr, newWritePtr - *(int *)(this + 0x1c));
}