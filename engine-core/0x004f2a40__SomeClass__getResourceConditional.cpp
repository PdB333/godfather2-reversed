// FUNC_NAME: SomeClass::getResourceConditional
undefined4 SomeClass::getResourceConditional(int param_2) {
    // param_2 acts as a flag: if non-zero, retrieve resource; else return 0
    if (param_2 != 0) {
        // this+0x4 points to an internal manager object
        // manager+0xc holds a handle/resource ID
        return FUN_004f23a0(*(undefined4 *)(*(int *)(this + 4) + 0xc));
    }
    return 0;
}