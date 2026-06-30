// Reversed from: FUN_0040d790
// Note: This function is a simple setter for a global byte-sized (undefined1) variable.
// It preserves the exact semantics of the original decompiled output.

#include <cstdint>

extern "C" {
    // Original binary had a global byte at address 0x0110ae74; give it a descriptive name.
    // Keep type as unsigned char to match undefined1 (one byte) from decompiler.
    extern unsigned char DAT_0110ae74;
    
    // The function sets the global variable to the provided byte value.
    void FUN_0040d790(unsigned char param_1)
    {
        DAT_0110ae74 = param_1;
        return;
    }
}

// REVERSED_FUNCTION: ::FUN_0040d790 (0x0040d790)