// FUNC_NAME: PlayerEquipment::clearWeaponSlot
void __thiscall PlayerEquipment::clearWeaponSlot(PlayerEquipment* this, void* weapon) {
    // weapon is a pointer to a weapon/item object.
    // +0x78: short slotType (0 = primary, 1 = secondary)
    // these offsets correspond to weapon slot pointers stored in this.
    // +0x10: primary weapon pointer
    // +0x14: secondary weapon pointer
    if (weapon != 0) {
        short slotType = *(short*)((uint8_t*)weapon + 0x78);
        if (slotType == 0) {
            if (weapon == *(void**)((uint8_t*)this + 0x10)) {
                *(void**)((uint8_t*)this + 0x10) = 0;
            }
        } else if (slotType == 1) {
            if (weapon == *(void**)((uint8_t*)this + 0x14)) {
                *(void**)((uint8_t*)this + 0x14) = 0;
            }
        }
    }
}