// FUNC_NAME: Entity::setBitFlag
void __thiscall Entity::setBitFlag(char enableFlag)
{
    // Offset 0x1d4 is a 16-bit flags field; set/clear bit 0 based on enableFlag
    if (enableFlag == '\x01') {
        *(ushort *)(this + 0x1d4) |= 1;
        return;
    }
    *(ushort *)(this + 0x1d4) &= 0xfffe;
}