// FUNC_NAME: Character::updateNeckBoneFlags
void Character::updateNeckBoneFlags() {
    // Call virtual method at vtable+0x9c (likely getBoneId or hasBone) for "m_neck1"
    bool hasNeckBone = (this->*vtbl->someMethod)("m_neck1") != 0;
    if (hasNeckBone) {
        // Set bit 0 and clear bit 2 in flags at offset 0x970 (0x25c * 4)
        this->flagsAt0x970 |= 1;
        this->flagsAt0x970 &= ~4;
    }
}