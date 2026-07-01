// FUNC_NAME: LuaManager::handleSetMoneyCommand
void __thiscall LuaManager::handleSetMoneyCommand(void *this, const char *luaStringArg)
{
    char *strPtr = nullptr;
    int unkZero_1 = 0;
    int unkZero_2 = 0;
    void (*funcPtr)() = nullptr;  // Not assigned in decompilation – likely a decompiler artifact

    // Resolve a C string from the Lua argument (likely lua_tostring equivalent)
    FUN_00604000(luaStringArg, &strPtr, 1);

    char *finalStr = strPtr;
    if (strPtr == nullptr) {
        finalStr = (char *)&DAT_0120546e;  // fallback empty string or "0"
    }

    // Invoke the "SetMoney" binding: (name, param1, param2, param3, value)
    FUN_005a04a0("SetMoney", 0, &DAT_00d83ad0, 1, finalStr);

    if (strPtr != nullptr) {
        funcPtr(strPtr);   // Suspect – funcPtr is null; likely missing assignment from call
    }
}