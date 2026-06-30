// FUNC_NAME: EARSObject::computeShadowState(uint8 EARSObject::computeShadowState(ShadowOverrideTable* table))
bool __fastcall EARSObject::computeShadowState(ShadowOverrideTable* table)
{
    // +0x10: entity unique ID (int)
    // +0x14: flags byte, bit0 = base shadow enable
    uint8_t baseFlag = this->flags & 1;
    int32_t index = table->entryCount - 1;

    // Search table backward for matching entity ID
    if (index >= 0)
    {
        ShadowEntry* entry = &table->entries[index];
        while (entry->id != *(int32_t*)((uint8_t*)this + 0x10))
        {
            index--;
            entry--;
            if (index < 0)
            {
                return baseFlag; // Not found, return base flag
            }
        }

        // Found matching entry, check override flags
        if (index >= 0)
        {
            uint32_t overrideFlags = entry->flags;
            if (overrideFlags & 1)      // Force shadow ON
            {
                return 1;
            }
            if (overrideFlags & 2)      // Force shadow OFF
            {
                baseFlag = 0;
            }
        }
    }

    return baseFlag;
}