// FUNC_NAME: UpdateManager::dispatchSlicedUpdate
void UpdateManager::dispatchSlicedUpdate(void* object, uint* modulusPtr)
{
    // Global tick counter (used for time-sliced processing)
    uint tickCount = DAT_01205220;
    uint modulus = *modulusPtr;
    uint groupIndex = tickCount % modulus;

    // Each group contains 3 slots (0x6c = 3 * 0x24 = 3 * 36 bytes)
    // UpdateSlot structure at offset 0x14 from object base
    UpdateSlot* slots = (UpdateSlot*)((uint)object + 0x14 + groupIndex * 0x6c);
    int slotCount = 3;

    // Overflow check (always true for normal values)
    if (groupIndex * 3 < groupIndex * 3 + 3) 
    {
        // Process the three slots in this group
        for (int i = 0; i < slotCount; ++i)
        {
            // Active flag at offset 12 (byte)
            if (slots[i].active)
            {
                // If the first dword is null, call the default handler from 20 bytes back
                if (slots[i].functionPtr == nullptr)
                {
                    // Function pointer at slot - 20 bytes (previous slot's context area)
                    void (*handler)() = *(void (**)())((uint)&slots[i] - 20);
                    if (handler)
                        handler();
                }
                else
                {
                    // Otherwise call the specific function with the context pointer (20 bytes before this slot)
                    void* context = (void*)((uint)&slots[i] - 20);
                    slots[i].functionPtr(context);
                }
            }
        }
    }
}