// FUNC_NAME: BaseObject::setFlagBit2
// Address: 0x00624ca0 - Sets or clears bit 2 (0x4) of the flags field at +0x14
void __thiscall BaseObject::setFlagBit2(BaseObject* this, char enable)
{
    // Toggle bit 2 (value 0x4) in flags at offset 0x14
    if (enable != '\0') {
        *(unsigned int*)((char*)this + 0x14) |= 4;      // +0x14: flags field
    } else {
        *(unsigned int*)((char*)this + 0x14) &= ~4u;
    }
}