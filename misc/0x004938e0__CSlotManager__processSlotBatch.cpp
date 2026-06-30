// FUNC_NAME: CSlotManager::processSlotBatch

void CSlotManager::processSlotBatch()
{
    // Array of 3 slot IDs stored at +0x1C0
    uint32_t* slotIdPtr = reinterpret_cast<uint32_t*>(this + 0x1C0);
    int remainingSlots = 3;
    // Temporary buffer (0x4C bytes) for slot data
    char slotBuffer[76];

    do {
        // Begin slot processing – may lock or synchronize access
        beginSlotOperation();            // FUN_00417560
        // Update internal state related to the slot
        updateSlotState();               // FUN_0048EE40
        // Fetch slot data into the buffer using the manager at +0x14 and current slot ID
        fillSlotBuffer(*(void**)(this + 0x14), *slotIdPtr, slotBuffer); // FUN_0060B020
        slotIdPtr++;
        remainingSlots--;
    } while (remainingSlots != 0);
}