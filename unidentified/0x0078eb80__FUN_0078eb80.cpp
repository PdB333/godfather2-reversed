// FUNC_NAME: SomeClass::isFlagSet
bool __thiscall isFlagSet(int this, byte flagIndex)
{
    // +0x2e: bitfield of flags
    if (*(byte *)(this + 0x2e) == 0) {
        return true;
    }
    return (1 << (flagIndex & 0x1f) & *(byte *)(this + 0x2e)) != 0;
}