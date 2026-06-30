//FUNC_NAME: AptValue::assertIsLookup
// Function address: 0x005a3900
// Role: Debug assertion for AptValue::isLookup() check. Part of EA's APT UI system.
// Calls a check function (0x005a3b80) and if it fails, triggers a debug breakpoint via SEH.

#include <windows.h> // for FS segment access, swi(3) is __debugbreak

// Forward declaration of the check function
bool isLookupCheck(); // 0x005a3b80

// Global assertion enabled flag (DAT_01128f66)
static bool s_assertEnabled = true; // initialized elsewhere

void AptValue::assertIsLookup()
{
    // If the check passes, no assertion needed
    if (isLookupCheck())
    {
        return;
    }

    // Assertion data (hardcoded for this specific check)
    const char* expr = "isLookup()";
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line = 0xbe; // 190
    int severity = 2; // assertion severity level
    bool* assertFlag = &s_assertEnabled;

    if (s_assertEnabled)
    {
        // Access thread-local exception handler list (FS:[0x2C] -> EXCEPTION_REGISTRATION)
        // This is a typical EA assertion mechanism that may throw or break.
        int* pExceptionReg = *(int**)(*(int**)(__readfsdword(0x2C)) + 0x30);
        unsigned int flags = 1;

        if (pExceptionReg == nullptr)
        {
            flags = 1; // default
        }
        else
        {
            // Call a function from the exception handler structure (offset +8)
            // This likely handles the assertion (e.g., log, break, or throw)
            flags = (*(unsigned int (__cdecl**)(const char**, const char*))(*pExceptionReg + 8))(&expr, "isLookup()");
        }

        // If the handler indicates we should break (flags & 2) and assertFlag is valid
        if ((flags & 2) != 0 && assertFlag != nullptr)
        {
            *assertFlag = false; // disable further assertions
        }

        // Trigger debug breakpoint if conditions are met
        if ((pExceptionReg != nullptr || severity != 4) &&
            ((flags & 1) != 0 || (severity == 0 || severity == 1)))
        {
            __debugbreak(); // swi(3) on x86
        }
    }
}