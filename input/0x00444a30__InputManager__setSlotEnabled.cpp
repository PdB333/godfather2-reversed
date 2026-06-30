// FUNC_NAME: InputManager::setSlotEnabled
void __thiscall InputManager::setSlotEnabled(int this, uint slotIndex, char newState) {
    // Max 16 controller slots (XInput 0x10 = 16)
    if (slotIndex >= 0x10) return;

    // Array of slot structures at this+0x14, each 0x18 bytes
    int slotBase = this + 0x14 + slotIndex * 0x18;

    // If slot is valid, update its flags at offset +8 (0x4 = bit 2, likely "enabled" flag)
    if (slotBase != 0) {
        uint* flags = (uint*)(slotBase + 8);
        if (newState != '\0') {
            *flags |= 4;
            // Notify controller state change (param_2 = slot index, bytes at this+0x195/0x196 = device context)
            FUN_00410b40(slotIndex, *(byte*)(this + 0x195), *(byte*)(this + 0x196));
        } else {
            *flags &= 0xfffffffb; // clear bit 2
        }
    }
}