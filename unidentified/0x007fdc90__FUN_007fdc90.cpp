// FUNC_NAME: UnknownClass::updateSomeSystem
uint __thiscall UnknownClass::updateSomeSystem(void* thisPtr, int param) {
    uint result = 0;
    int* statePtr = (int*)((char*)thisPtr + 0x1c78);
    if (*statePtr != 0 && *statePtr != 0x48) {
        int val1 = getSomeContainer();   // FUN_00471610
        int val2 = getSomeContainer();   // FUN_00471610 (second call)
        result = processTransformUpdate(val2 + 0x30, val1 + 0x30, val1 + 0x20, param); // FUN_007f7f30
    }
    return result;
}