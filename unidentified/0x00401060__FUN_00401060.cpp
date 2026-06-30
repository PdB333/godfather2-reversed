// Reconstructed C++23 equivalent of FUN_00401060 at 0x00401060
// Behavior mirrors the decompiled function:
// - If *param_1 != 0, call the function pointer stored at param_1[3] with param_1 as argument.
// - Then zero out *param_1, param_1[2], and param_1[1].
// - No return value.

#include <cstdint>

void FUN_00401060(int* param_1) {
    if (param_1 == nullptr) {
        // If the input is null, nothing to do per the original logic (would dereference null otherwise).
        return;
    }

    if (*param_1 != 0) {
        // Retrieve the function pointer from the 4th slot (index 3) and invoke it with param_1.
        using FPtr = void(*)(int*);
        FPtr func = reinterpret_cast<FPtr>(param_1[3]);
        if (func != nullptr) {
            func(param_1);
        }
    }

    // Reset the tracked fields to zero, preserving the original order and semantics.
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
}

// End marker
REVERSED_FUNCTION: ::FUN_00401060 (0x00401060)