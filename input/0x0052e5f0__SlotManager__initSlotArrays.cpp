// FUNC_NAME: SlotManager::initSlotArrays
void SlotManager::initSlotArrays(void)
{
    int slotIndex = 0;
    uint sourceOffset = 0;
    do {
        g_slotFlags[slotIndex] = 0;                          // +0x19708 array of int32 flags
        g_slotInitialValues[slotIndex] = *(int32_t *)((uint8_t *)g_slotConfigTable + sourceOffset); // copy first DWORD of each 24-byte config entry
        g_slotCounters[slotIndex] = 0;                        // +0x19808 array of int32 counters
        sourceOffset += 0x18;                                 // 24 bytes per config entry
        slotIndex = slotIndex + 1;
    } while (sourceOffset < 0x300);                            // 32 iterations (0x300/0x18 = 32)
}