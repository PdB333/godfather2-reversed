// FUNC_NAME: GameObject::setFlag256
void __thiscall GameObject::setFlag256(char enable)
{
    // offset 0x4c: uint32_t flags (bitfield)
    uint32_t* flags = (uint32_t*)((char*)this + 0x4c);
    if (enable != '\0') {
        *flags |= 0x100;  // set bit 8
    } else {
        *flags &= ~0x100; // clear bit 8
    }
    return;
}