// FUNC_NAME: AptValue::assertIsObject
void __cdecl AptValue::assertIsObject(void)
{
    // Check if assertions are enabled
    if (isAssertEnabled()) {
        return;
    }

    // Assertion data: expression, file, line, level
    const char* expression = "isObject()";
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line = 0x131; // 305
    int level = 2; // Assertion severity level
    void* debugBuffer = (void*)((int)&PTR_DAT_01128fb0 + 1); // Pointer to debug output buffer

    // Check if debug output is active
    if (PTR_DAT_01128fb0._1_1_ != '\0') {
        // Get thread-local storage data
        int* localData = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
        uint flags = 1;
        if ((localData == (int*)0x0) ||
            (flags = (**(code**)(*localData + 8))(&expression, "isObject()"), debugBuffer != (void*)0x0))
        {
            if ((flags & 2) != 0) {
                *debugBuffer = 0; // Clear debug buffer
            }
        }
        // Trigger breakpoint if conditions are met
        if (((localData != (int*)0x0) || (level != 4)) &&
            ((flags & 1) != 0 || (level == 0 || level == 1))) {
            code* breakpoint = (code*)swi(3); // Software interrupt for debug break
            (*breakpoint)();
            return;
        }
        return;
    }
    return;
}