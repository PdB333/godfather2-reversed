// FUNC_NAME: EntityFlags::setFlags
void __thiscall EntityFlags::setFlags(uint flags)
{
    uint oldFlags = *(uint *)(this + 4);   // +0x04: current flags
    uint newFlags = oldFlags | flags;
    *(uint *)(this + 4) = newFlags;
    if (newFlags != oldFlags) {
        *(byte *)(this + 8) = 1;           // +0x08: dirty flag (set to 1 when flags change)
    }
    return;
}