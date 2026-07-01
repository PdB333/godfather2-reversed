// FUNC_NAME: SomeClass::setFlag
void __thiscall SomeClass::setFlag(char flag) {
    // +0x209: boolean flag (e.g., active, enabled, or state toggle)
    *(char *)(this + 0x209) = flag;
    // Update internal state after flag change (FUN_00873bb0)
    updateState();
}