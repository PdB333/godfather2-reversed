// FUNC_NAME: getFlagMask
// Address: 0x006c9470
// Role: Calls virtual method at vtable+0x10 to test a flag; returns the flag bit if set, otherwise 0.
uint getFlagMask(void* obj, uint flag) {
    uint dummy = 0;
    // Virtual call: this->vtable[0x10](flag, &dummy) returns bool
    bool isSet = (*(char (__thiscall**)(void*, uint, uint*))(*(uint*)obj + 0x10))(obj, flag, &dummy) != 0;
    return isSet ? flag : 0;
}