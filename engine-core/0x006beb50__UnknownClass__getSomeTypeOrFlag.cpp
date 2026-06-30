// FUNC_NAME: UnknownClass::getSomeTypeOrFlag
uint __fastcall getSomeTypeOrFlag(void* thisPtr)
{
    // +0x34: byte flags, bit0 set = has property?
    // +0x18: pointer to sub-object A (component?).
    // +0x14: pointer to sub-object B.
    // +0x2c: int field (probably counter or status)
    // Sub-object offset +0x54: likely class identifier hash.
    if (((*(uint8*)((int)thisPtr + 0x34) & 1) != 0) &&
        ((*(int*)(*(int*)((int)thisPtr + 0x18) + 0x54) == 0x637b907) ||
         (*(int*)(*(int*)((int)thisPtr + 0x14) + 0x54) == 0x637b907)))
    {
        return 0x637b900;
    }
    return (uint)(*(int*)((int)thisPtr + 0x2c) == 0);
}