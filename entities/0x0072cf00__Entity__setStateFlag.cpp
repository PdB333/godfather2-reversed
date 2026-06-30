// FUNC_NAME: Entity::setStateFlag
void __thiscall Entity::setStateFlag(bool enable)
{
    // Flags field at +0x1F58.
    // Bit 0x10 (bit 4) is set when enable is true.
    // Bit 0x20 (bit 5) is set when enable is false.
    uint flags = *(uint *)(this + 0x1F58);
    if (enable) {
        flags |= 0x10;
    } else {
        flags |= 0x20;
    }
    *(uint *)(this + 0x1F58) = flags;
}