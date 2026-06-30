// FUNC_NAME: GameObject::setFlagBit1
void __thiscall GameObject::setFlagBit1(GameObject* this, char enabled) {
    // Flags field at offset +0x18, bit 1 (value 2) is being manipulated.
    uint32_t* flags = (uint32_t*)((uint8_t*)this + 0x18);
    if (enabled != 0) {
        *flags |= 2;  // Set bit 1
    } else {
        *flags &= ~2; // Clear bit 1
    }
}