// FUNC_NAME: LuaVariableGet
int LuaVariableGet(LuaState* L) {
    // Get a variable handle from Lua stack (index 1)
    int* handle = (int*)LuaGetVariableHandle(1, "Variable");
    if (handle != nullptr) {
        if (*handle != -1) {
            // Access global variable array at offset 0x24 from base address DAT_01223428
            // +0x24 is likely a pointer to an array of variable definitions
            // Each entry is 0x14 bytes, and handle indexes into it
            int* globalArray = *(int**)(DAT_01223428 + 0x24);
            int entryOffset = 8 + *handle * 0x14;
            LuaPushValue(L, *(undefined4*)(globalArray + (entryOffset >> 2)));
            return 1;
        }
        LuaReportError("LuaVariableGet: Invalid variable handle.");
    }
    LuaReportError("LuaVariableGet: Expected variable handle, but found something else.\n");
    // Software interrupt 3 - likely assertion failure
    ((void(*)(void))swi(3))();
    return 0; // Unreachable
}