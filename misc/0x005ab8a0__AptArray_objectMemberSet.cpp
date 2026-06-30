// Xbox PDB: AptArray::objectMemberSet
// FUNC_NAME: AptArray::parseSizeFromString
// Function address: 0x005ab8a0
// Role: Parses an integer from a string and sets the array size, with debug assertion checks.
// File: ..\source\Apt\AptArray.cpp (indicated by debug info)

#include <cstdlib> // for atol

// External globals and functions (from Ghidra naming, need actual definitions)
extern int g_aptParseEnabled; // DAT_0103af70 – global flag enabling this parse path
extern int g_assertEnableFlag; // DAT_01128fd0 – controls debug assertion output
extern int* __security_cookie; // FS:[0x2c] +0x30 (typical MSVC debug heap)
extern void assertFailureBreakpoint(); // swi(3) / int3 handler

// Forward declarations for called functions
extern bool isAssertEnabled(); // FUN_0059c500 – returns non-zero if assertions active
extern void setArraySize(int size); // FUN_0059c450 – sets the array capacity
extern void applyArraySize(int size); // FUN_005ab520 – applies the size to internal structures

int AptArray::parseSizeFromString(char* str, int fallbackSize)
{
    // Enable the parse path globally
    g_aptParseEnabled = 1;

    // Debug assertion: verify current context is an array
    if (isAssertEnabled())
    {
        const char* expression = "pContext->isArray()";
        const char* filename = "..\\source\\Apt\\AptArray.cpp";
        const int line = 0xe1;
        int assertLevel = 2; // 2 = probably "should not happen" level

        if (g_assertEnableFlag != 0)
        {
            // FS:[0x2c] +0x30 points to debug heap info; used for assert dialog
            int* heapInfo = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30);
            unsigned int result = 1;
            if (heapInfo != nullptr)
            {
                // Call a debug reporting function through a vtable
                auto reportFunc = (code *)(*heapInfo + 8);
                result = reportFunc(&expression, "pContext->isArray()");
            }
            if ((result & 2) != 0)
            {
                g_assertEnableFlag = 0; // disable further asserts if "break" requested
            }
            // If unrecoverable, trigger debug break
            if (((heapInfo != nullptr) || (assertLevel != 4)) &&
                ((result & 1) != 0 || (assertLevel == 0 || assertLevel == 1)))
            {
                assertFailureBreakpoint();
            }
        }
    }

    // Parse the string to integer
    long parsedValue = atol(str);
    if (parsedValue == 0 && *str != '0')
    {
        return 0; // conversion failed
    }

    // Use the parsed value, or fallback if provided
    int size = parsedValue; // atol returns long, assign to int
    if (fallbackSize != 0)
    {
        size = fallbackSize;
    }

    // Apply the size to the array
    setArraySize(size);
    applyArraySize(size);
    return 1; // success
}