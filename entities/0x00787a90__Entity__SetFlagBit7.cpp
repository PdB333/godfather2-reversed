// FUNC_NAME: Entity::SetFlagBit7
// Sets or clears bit 7 (0x80) of the flags field at offset +0x2c6c.
// Calls OnFlagChanged() if the value actually changes.
void __thiscall Entity::SetFlagBit7(byte enable)
{
    uint flags = *(uint *)((char *)this + 0x2c6c);
    bool current = (flags >> 7) & 1;
    if (enable != current)
    {
        if (enable == 0)
        {
            *(uint *)((char *)this + 0x2c6c) = flags & 0xffffff7f;
        }
        else
        {
            *(uint *)((char *)this + 0x2c6c) = flags | 0x80;
            FUN_007872c0(); // OnFlagChanged
        }
    }
}