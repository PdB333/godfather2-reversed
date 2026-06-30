// FUNC_NAME: CharacterFamilyManager::updateFamilySlotReferences
void __thiscall CharacterFamilyManager::updateFamilySlotReferences(int this, int familyTableBase, int slotValue)
{
    // this +0x50: pointer to array of family slot structures (each 0xB0 bytes)
    int slotArrayStart = *(int *)(this + 0x50);
    // this +0x34: number of slots (count)
    int slotCount = *(int *)(this + 0x34);
    int slotArrayEnd = slotArrayStart + slotCount * 0xB0;

    for (int slotPtr = slotArrayStart; slotPtr != slotArrayEnd; slotPtr += 0xB0)
    {
        // slot structure offsets:
        // +0x29: family/type byte (0 = neutral, 2/3 = specific families)
        byte familyByte = *(byte *)(slotPtr + 0x29);
        // +0x2A: short index into sub-array
        short index = *(short *)(slotPtr + 0x2A);

        // Only process slots with valid index and allowed family types
        if (index >= 0 &&
            (familyByte == 0 || (familyByte > 1 && familyByte < 4)))
        {
            // familyTableBase +0x1240: table of family data (each entry 0x6A0 bytes)
            int familyEntryPtr = *(int *)(familyTableBase + 0x1240 + (int)familyByte * 0x6A0);
            // within family entry, offset +0x1C: array of pointers (each 0x20 bytes apart)
            int *destSlot = (int *)(familyEntryPtr + 0x1C + index * 0x20);
            *destSlot = slotValue;  // original code used uninitialized EDI; this parameter replaces it
        }
    }
}