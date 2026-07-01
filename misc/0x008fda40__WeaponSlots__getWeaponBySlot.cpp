// FUNC_NAME: WeaponSlots::getWeaponBySlot

uint32_t __thiscall WeaponSlots::getWeaponBySlot(int thisPtr, int slot) {
    // slot is 1-based (1, 2, or 3)
    uint32_t index = slot - 1;
    uint32_t result = 0;

    if (index < 3) {
        // Check if the slot is occupied (flag at offset +0x7c + index*8)
        if (*(char*)(thisPtr + 0x7c + index * 8) != 0) {
            // Return the weapon handle stored at offset +0x78 + index*8
            result = *(uint32_t*)(thisPtr + 0x78 + index * 8);
        }
    }
    return result;
}

/*
Structure layout:
Offset +0x78: Array of 3 entries, each 8 bytes:
    +0x00: weaponHandle (uint32_t)
    +0x04: slotOccupied (uint8_t) (non-zero means occupied)
    +0x05-0x07: padding
*/