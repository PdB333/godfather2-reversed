// FUN_005e63e0: StreamManager::releaseSlot(uint slotIndex)
bool StreamManager::releaseSlot(uint slotIndex)
{
    bool result = false;
    // Check if slot array (at this+0x603c) exists and index is within max 512
    if ((this->slotArray != 0) && (slotIndex < 0x200))
    {
        // Each slot is 0x74 bytes; array base is at this+0x603c
        int* slot = (int*)(slotIndex * 0x74 + this->slotArray);
        if (slot != 0)
        {
            // slot[2] is offset +0x08 – secondary resource pointer
            if (slot[2] != 0)
            {
                FUN_005f1ef0(slot[2]);
            }
            // slot[0] is offset +0x00 – primary data pointer
            if (slot[0] != 0)
            {
                FUN_005dbc10(slotIndex, slot[0]);
                FUN_005e5200(0);
                slot[0] = 0;
                return 1;
            }
            FUN_005dbc10(slotIndex, 0);
            result = 1;
        }
    }
    return result;
}