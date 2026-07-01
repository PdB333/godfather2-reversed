// FUNC_NAME: DataSlotManager::setSlotData
void __thiscall DataSlotManager::setSlotData(int this, int slotId, void* data1, void* data2)
{
    // Check flag bit 0 is clear (not locked/disabled)
    if ((*(byte *)(this + 0x6f4) & 1) == 0)
    {
        uint slotIndex = 0;
        int slotCount = *(int *)(this + 0x33c); // number of slots
        if (slotCount != 0)
        {
            int* slotArray = *(int**)(this + 0x338); // array of slot pointers
            // Linear search for slot with matching ID at slot+0x5c
            while (*(int*)(*slotArray + 0x5c) != slotId)
            {
                slotIndex++;
                slotArray++;
                if (slotCount <= slotIndex)
                {
                    return; // not found
                }
            }
            // Found the slot
            void** slotPtr = (void**)(*(int**)(this + 0x338))[slotIndex];
            if (slotPtr != nullptr)
            {
                slotPtr[0] = data1; // first data field
                slotPtr[1] = data2; // second data field
                // If game state is not 3, reset some timer/counter
                if (*(int*)(this + 0xdc) != 3)
                {
                    *(int*)(this + 0xc4) = 0;
                }
                // Set dirty flag bit 2
                *(uint*)(this + 0x6f4) |= 4;
                // Notify of data change
                FUN_00964500(data1, data2, slotId);
            }
        }
    }
}