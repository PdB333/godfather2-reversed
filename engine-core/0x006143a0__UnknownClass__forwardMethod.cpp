// FUNC_NAME: UnknownClass::forwardMethod
void __thiscall UnknownClass::forwardMethod(void* param2, void* param3, void* param4, void* param5)
{
    // Reorders parameters: passes (param2, param3, param4, param5, this)
    // Likely calls a static/global function that expects 'this' as last argument
    FUN_006145f0(param2, param3, param4, param5, this);

    // Check global debug flag (bit 0) – maybe enable logging?
    if ((DAT_011f7430 & 1) != 0) {
        FUN_00614b90(); // Possibly debug/logging function
    }
}