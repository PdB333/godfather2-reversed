// Xbox PDB: AptValue::c_float
// FUNC_NAME: AptValue::assertIsFloat
// Address: 0x005a7440
// Role: Assertion failure handler for isFloat() check in _AptValue.h (line 205)
// On failure, may break into debugger via software interrupt (swi(3)) if debug flag is set.

#include <cstdint>
#include <cstddef>

// Forward declaration of the condition checker (FUN_005a7df0)
extern bool _isAssertConditionMet(void);

// Global debug assertion flag (DAT_01128fa8)
extern uint8_t g_debugAssertEnabled;

void AptValue::assertIsFloat(void)
{
    // First, check if the condition passes; if so, no assertion needed.
    if (_isAssertConditionMet())
    {
        return;
    }

    // Assertion failed – record source info (hardcoded for this specific call)
    const char* expression = "isFloat()";
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line = 0xcd; // 205

    // Check if debug assertion handling is enabled
    if (g_debugAssertEnabled)
    {
        // Complex debug check – typical for EA engine assertions:
        // Access thread-local storage (fs:[0x2c]) and verify stack integrity.
        // If checks pass, clear the assertion flag; otherwise trigger a breakpoint.
        int* fsBase = *(int**)(__readfsdword(0x2c) + 0x30);
        uint32_t flags = 1;

        if (fsBase != nullptr)
        {
            flags = (*(uint32_t(__thiscall**)(int*, const char**, const char*))(*(uint32_t*)fsBase + 8))(
                &expression, "isFloat()");
        }

        if (flags & 2)
        {
            *((uint8_t*)expression) = 0; // Clear the expression string? (unusual, likely a debug marker)
        }

        // Additional check: break if flags indicate a break condition
        bool shouldBreak = false;
        if (fsBase != nullptr)
        {
            if (flags & 1 || ((flags & 1) == 0 && (flags == 0 || flags == 1)))
            {
                shouldBreak = true;
            }
        }
        else if (flags & 1 || ((flags & 1) == 0 && (flags == 0 || flags == 1)))
        {
            shouldBreak = true;
        }

        if (shouldBreak)
        {
            // Trigger debug breakpoint (software interrupt 3)
            __debugbreak();
        }
    }
}