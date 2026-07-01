// FUNC_NAME: Entity::setFlagBit1
void __thiscall Entity::setFlagBit1(Entity* this, bool enable) {
    unsigned short* flags = (unsigned short*)((int)this + 0xC8); // flags at +0xC8
    if (enable) {
        *flags |= 2;  // set bit 1
    } else {
        *flags &= ~2; // clear bit 1
    }
}