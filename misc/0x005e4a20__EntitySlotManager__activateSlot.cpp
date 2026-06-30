// FUNC_NAME: EntitySlotManager::activateSlot
void __thiscall EntitySlotManager::activateSlot(EntitySlotManager *this, int tableBase)
{
    uint slotId = EntitySlotManager::getSlotId(tableBase, this); // returns a handle/ID
    if (slotId != 0 && (slotId & 0xFFFF) < 0x200) // max 512 slots
    {
        int slotEntry = (slotId & 0xFFFF) * 0x30 + 0x10 + tableBase; // slot at tableBase+0x10
        if (slotEntry != 0 && *(uint *)(slotEntry + 0x2C) == slotId) // validate slot ID
        {
            uint32 value32 = *(uint32 *)((char *)this + 4); // field at this+4
            uint8 value8 = *(uint8 *)this;                 // field at this+0
            if (slotEntry != 0)
            {
                *(uint32 *)(slotEntry + 0x18) = 2;                                  // mark slot state = 2 (active)
                int subObj = *(int *)(slotEntry + 0x10);                            // pointer to sub-object
                *(short *)(subObj + 0x5A) = (short)value32;                        // set some 16-bit field
                *(byte *)(subObj + 0x58) = value8;                                 // set some 8-bit field
            }
        }
    }
}