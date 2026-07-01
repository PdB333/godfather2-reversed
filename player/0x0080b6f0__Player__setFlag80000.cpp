// FUNC_NAME: Player::setFlag80000
void __thiscall Player::setFlag80000(bool enable)
{
    // offset 0x1b94: flags field (uint32)
    uint& flags = *(uint*)((char*)this + 0x1b94);
    if (enable)
    {
        flags |= 0x80000; // set bit 19
    }
    else
    {
        flags &= ~0x80000; // clear bit 19
    }
}