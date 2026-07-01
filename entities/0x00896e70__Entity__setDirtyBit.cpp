// FUNC_NAME: Entity::setDirtyBit
void __fastcall Entity::setDirtyBit(int thisPtr)
{
    // +0x58: flags field; set bit 1 (value 2) to mark object dirty
    *(uint *)(thisPtr + 0x58) |= 2;
}