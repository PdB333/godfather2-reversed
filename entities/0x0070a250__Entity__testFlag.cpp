// FUNC_NAME: Entity::testFlag
uint Entity::testFlag(uint flag) {
    int dummy = 0;
    // vtable offset 0x10: virtual bool checkFlag(uint flag, int* outValue)
    auto vfunc = (bool (__thiscall*)(void*, uint, int*))(*(uint32_t**)this)[4];
    bool result = vfunc(this, flag, &dummy);
    return result ? flag : 0;
}