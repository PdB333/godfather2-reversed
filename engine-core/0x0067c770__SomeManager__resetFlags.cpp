// FUNC_NAME: SomeManager::resetFlags
void __thiscall SomeManager::resetFlags() {
    // 0067c770 - reset state flags
    if (gSomeManager) {
        clearGlobalFlags();
        *(char*)(gSomeManager + 0x90) = 0;  // +0x90: likely active flag
    }
    *(char*)(this + 9) = 1;  // +0x9: likely initialized or ready flag
}