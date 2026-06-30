// FUNC_NAME: SlotManager::setSlotFromObject
void __thiscall SlotManager::setSlotFromObject(SlotManager* this, SlotTable* slotTable)
{
    uint slotId = FUN_005e4a80(slotTable, /* third param is unknown, likely 0 */ 0, this);
    // FUN_005e4a80 returns a validated slot ID or 0
    if (slotId != 0 && (slotId & 0xFFFF) < 0x200)
    {
        SlotEntry* entry = &slotTable->entries[slotId & 0xFFFF]; // entry size 0x30, offset 0x10
        if (entry->magic == slotId) // offset +0x2c
        {
            // this object has byte at offset 0, dword at offset 4
            char objectType = *(char*)this;           // offset 0x0
            int objectValue = *(int*)((char*)this + 4); // offset 0x4

            entry->state = 2; // offset +0x18 (write 2)
            entry->target->someShort = (short)objectValue;  // offset +0x10 -> +0x5a
            entry->target->someByte = objectType;           // offset +0x10 -> +0x58
        }
    }
}