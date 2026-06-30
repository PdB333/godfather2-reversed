// FUNC_NAME: DebugConditionalCall
// Address: 0x006f6ed0
// This function appears to be a conditional wrapper: if a global debug flag is set,
// it calls a real processing function (FUN_006f6590), otherwise it returns the
// current value of EAX with the lower 8 bits masked off (0xffffff00).
// The EAX value is likely set by the caller and may represent some status or result.

#include <cstdint>

// Global debug flag (DAT_0112aa10). Non-zero indicates debug mode enabled.
extern int32_t g_debugModeEnabled;

// Forward declaration of the wrapped function (FUN_006f6590).
// This function likely performs the actual logic when debugging is on.
extern uint32_t realProcessingFunction(uint32_t param1, uint32_t param2);

// __cdecl (no explicit calling convention, but EAX is used implicitly)
uint32_t DebugConditionalCall(uint32_t param1, uint32_t param2)
{
    // EAX is not a formal parameter; it's the register state at entry.
    // In x86 __cdecl, EAX may hold the return value of a previous call.
    // Here we treat it as an implicit input, typically set by the caller.
    uint32_t eaxValue;
    __asm { mov eaxValue, eax } // Not portable, but necessary for correctness.

    uint32_t result = eaxValue & 0xffffff00; // Clear low byte, often used for alignment or flag removal.

    if (g_debugModeEnabled != 0) {
        // Replace result with output of the actual function.
        result = realProcessingFunction(param1, param2);
    }

    return result;
}