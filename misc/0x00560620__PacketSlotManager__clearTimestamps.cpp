// FUNC_NAME: PacketSlotManager::clearTimestamps
void __thiscall PacketSlotManager::clearTimestamps(void)
{
    // Read count and array pointer from this
    // +0x48: pointer to array of SlotData structures (each 0xc0 bytes)
    // +0x4c: number of elements in the array
    int count = *(int*)((char*)this + 0x4c);
    SlotData* array = *(SlotData**)((char*)this + 0x48);

    // Zero out the four timestamp/state fields for each slot
    // Slot structure offsets:
    // +0xa8: fieldA8 (e.g., sendTime)
    // +0xac: fieldAC (e.g., receiveTime)
    // +0xb0: fieldB0 (e.g., sequence number)
    // +0xb4: fieldB4 (e.g., acknowledgment flags)
    for (int i = 0; i < count; i++)
    {
        array[i].fieldA8 = 0;
        array[i].fieldAC = 0;
        array[i].fieldB0 = 0;
        array[i].fieldB4 = 0;
    }
}