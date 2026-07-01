// FUNC_NAME: initAndReturnThis
#include <cstdint>

// Reconstructed from Ghidra at address 0x008ebcd0
// This function is a trivial wrapper that calls an initialization routine
// and returns the 'this' pointer (passed as the first parameter via __fastcall).
// The called function at 0x008ea6a0 is likely a one-time global initializer or
// a base class constructor.

static void __fastcall baseInit(void); // Forward declaration of FUN_008ea6a0

uint32_t __fastcall initAndReturnThis(uint32_t thisPtr)
{
    baseInit(); // Perform base/global initialization (no arguments)
    return thisPtr; // Return the object pointer for chaining
}