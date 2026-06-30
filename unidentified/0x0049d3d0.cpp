// FUN_0049d3d0: GameCharacter::assignRandomFamilySlot
void GameCharacter::assignRandomFamilySlot()
{
    // +0x0C: role (byte) - set to AI_SOLDIER (6)
    *reinterpret_cast<unsigned char*>(reinterpret_cast<uint32_t>(this) + 0x0C) = 6;

    // +0x10: crewSlotId (uint32) - store random family slot index
    uint32_t slotIndex = getRandomFamilyIndex(); // FUN_00611000 - returns random index or -1
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(this) + 0x10) = slotIndex;

    if (slotIndex != 0xFFFFFFFF && slotIndex != 0)
    {
        // Validate slot: check bounds and that the slot's status is >= 2
        if (slotIndex > 0xFFF ||
            *reinterpret_cast<unsigned char*>(&g_familySlots[slotIndex]) < 2)
        {
            // Invalid slot, reset crewSlotId to 0
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(this) + 0x10) = 0;
            return;
        }
        // Slot is valid; increment the reference count at offset 0x10 of the slot structure
        if (slotIndex < 0x1000)
        {
            int** refPtr = reinterpret_cast<int**>(
                reinterpret_cast<uint32_t>(&g_familySlots[slotIndex]) + 0x10);
            if (*refPtr != nullptr)
            {
                **refPtr = **refPtr + 1;
            }
        }
    }
}