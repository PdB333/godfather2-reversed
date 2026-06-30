// FUNC_NAME: Entity::modifyFlags
void __thiscall Entity::modifyFlags(int* thisObj, uint newBits, uint clearBits)
{
    // Virtual function at vtable+0x5c takes combined mask and a sentinel (-1 = update all slots)
    typedef void (__thiscall *FlagApplyFunc)(uint, uint);
    FlagApplyFunc applyFunc = (FlagApplyFunc)(*(int*)thisObj + 0x5c);

    // Combine internal flags at offset 0x88 (thisObj[0x22]) with new bits, then clear specified bits
    applyFunc((thisObj[0x22] | newBits) & ~clearBits, 0xFFFFFFFF);
}