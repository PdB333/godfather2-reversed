// Xbox PDB: char const * __cdecl lua_typename(struct lua_State *,int)
// FUNC_NAME: LuaBindingIterator::getNextEnumString
int __thiscall LuaBindingIterator::getNextEnumString(LuaBindingIterator *this) {
    int *current = this->mCurrent;   // +0xC
    int *begin = this->mBegin;       // +0x8

    // Check if iterator is valid and current element is not a sentinel (-1)
    if (current >= begin || current == nullptr || *current == -1) {
        LuaError(this->L, 1, "value expected");  // 0x00627a20
        // Note: LuaError likely does not return (longjmp)
        // If it returns, the condition below still uses iVar2 from extraout_ECX
    }

    // After validation, retrieve string from global enum table
    int value = *current;
    if (value != -1) {
        PushString(this->L, g_enumStrings[value]);  // 0x00625ca0, table at 0x00e2a89c
        return 1;
    }

    PushString(this->L, "no value");
    return 1;
}