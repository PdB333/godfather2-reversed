// FUNC_NAME: Entity::getFlagMask
uint Entity::getFlagMask(uint flag) {
    bool dummy;
    // Virtual function at vtable+0x10: char CheckFlag(uint, bool*)
    // Returns non-zero character if the flag is set; the bool* output is unused.
    char result = ((char (__thiscall*)(Entity*, uint, bool*))(*(uint*)_this + 0x10))(_this, flag, &dummy);
    return (result != 0) ? flag : 0;
}