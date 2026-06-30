// FUNC_NAME: SlotManager::resetActiveSlots
void __thiscall SlotManager::resetActiveSlots(SlotManager *this)
{
    // SlotEntry array starts at this+0x24, each entry 12 bytes (0xc)
    // Structure: [uint index, uint activeFlag, ?uint pad?]
    uint *slotEntry = (uint *)((char *)this + 0x24);
    int slotCount = 0x200; // 512 slots

    do
    {
        // Check if slot is active (second dword non-zero)
        if (slotEntry[1] != 0)
        {
            uint dataIndex = *slotEntry;
            // Check if this data index should be cleared
            if (SlotManager::isSlotValid(dataIndex))
            {
                int dataBlock = 0;
                if (dataIndex < 0x200)
                {
                    // Data array starts at this+0x10, each element 0x30 bytes
                    dataBlock = (int)this + 0x10 + dataIndex * 0x30;
                }
                // Clear four fields at known offsets within the data block
                *(int *)(dataBlock + 0x20) = 0; // offset 0x20
                *(int *)(dataBlock + 0x18) = 0; // offset 0x18
                *(int *)(dataBlock + 0x2c) = 0; // offset 0x2c
                *(int *)(dataBlock + 0x10) = 0; // offset 0x10
            }
        }
        // Move to next slot entry
        slotEntry += 3; // 3 uint = 12 bytes
        slotCount--;
    } while (slotCount != 0);

    // Reset global state flags (DAT_01223504 is a global manager pointer)
    // Set byte at +0x1d to 0 and dword at +0x18 to 0
    // DAT_01223504 likely points to a global singleton of same class
    char *globalManager = (char *)DAT_01223504;
    globalManager[0x1d] = 0;
    *(int *)(globalManager + 0x18) = 0;
}