// FUNC_NAME: Player::setCurrentWeapon
// Address: 0x00731ef0
// Role: Updates the player's current weapon slot. Copies weapon data (16 bytes) from either an existing internal pointer or a new weapon pointer into a local buffer, and notifies the system of the change.

void __thiscall Player::setCurrentWeapon(void* thisPtr, void* newWeapon) {
    // Check if there is an existing weapon stored at +0x1ee4
    if (*(void**)((unsigned int)thisPtr + 0x1ee4) != 0) {
        // Copy 16-byte weapon data from the existing weapon into the local buffer at +0x3c
        memcpy((void*)((unsigned int)thisPtr + 0x3c), *(void**)((unsigned int)thisPtr + 0x1ee4), 0x10);
        // Notify that the old weapon data has been copied (event type 0)
        notifyWeaponChange(0, 0);
    }
    // If a new weapon is provided via parameter, copy its data into the same local buffer
    if (newWeapon != 0) {
        memcpy((void*)((unsigned int)thisPtr + 0x3c), newWeapon, 0x10);
        // Notify that a new weapon has been set (event type 1)
        notifyWeaponChange(1, 0);
    }
    return;
}