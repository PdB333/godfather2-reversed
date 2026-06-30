// FUNC_NAME: Player::getActiveSlotIndex
// Function address: 0x00578280
// Role: Returns the index of the active slot (weapon, target, etc.) based on a flag and a count.
// If flag bit 5 at +0x2C is set and count at +0x00 > 1, returns slot 2 at +0x1C; otherwise returns slot 1 at +0x14.

int __thiscall Player::getActiveSlotIndex(void) {
    // Check if flag bit 5 (0x20) is set at byte offset 0x2C
    if (((*(byte *)(this + 0x2C) & 0x20) != 0) && (*(int *)this > 1)) {
        // Return value from slot 2 (offset 0x1C)
        return *(int *)(this + 0x1C); // +0x1C: second slot index
    }
    // Otherwise return slot 1 (offset 0x14)
    return *(int *)(this + 0x14); // +0x14: first slot index
}