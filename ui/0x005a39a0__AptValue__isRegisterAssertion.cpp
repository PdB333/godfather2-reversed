// FUNC_NAME: AptValue::isRegisterAssertion
// Address: 0x005a39a0
// Role: Debug assertion handler for the condition "isRegister()" in _AptValue.h:200

void AptValue_isRegisterAssertion()
{
    // If asserts are globally suppressed, exit early (FUN_005a3d00 likely checks a flag)
    if (FUN_005a3d00())
        return;

    // Assertion metadata (hardcoded for this specific assert)
    char* expression = "isRegister()";
    char* file       = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line         = 200;
    int assertType   = 2;  // e.g., severity or break-once flag
    char* breakFlag  = &g_assertBreakEnabled;  // +0x0 global variable (DAT_01128f67)

    if (g_assertBreakEnabled != 0)
    {
        // TLS-based debug handler (__readfsdword(0x2c) -> GS segment)
        int* tlsNode = *(int**)(__readfsdword(0x2c) + 0x30);
        uint action = 1;
        if (tlsNode != nullptr)
        {
            // Call handler via vtable (+8)
            action = (*(code**)(*tlsNode + 8))(&expression, "isRegister()");
        }

        // Optionally disable the break flag
        if ((breakFlag != nullptr) && (action & 2) != 0)
            *breakFlag = 0;

        // Condition to trigger the actual breakpoint
        bool breakNow = false;
        if ((tlsNode != nullptr) || (assertType != 4))
        {
            if (!(action & 1) && (assertType != 0 && assertType != 1))
                breakNow = true;
        }
        else
        {
            breakNow = true;
        }

        if (breakNow)
            __debugbreak();  // original: swi(3)
    }
}