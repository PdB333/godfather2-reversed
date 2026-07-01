// FUNC_NAME: safeGetObjectHandle
// Function address: 0x00898330
// Role: Checks if a pointer (param_1) is non-null, then calls an underlying function (FUN_008981f0)
// to retrieve an object handle or perform an operation. Returns 0 if null.
// This is a common guard pattern used throughout the game's object management code.

#include <cstdint>

// Forward declaration of the underlying function (known from callee analysis)
extern uint32_t FUN_008981f0(uint32_t param_1);

uint32_t safeGetObjectHandle(uint32_t objectPtr) {
    if (objectPtr == 0) {
        return 0;
    }
    return FUN_008981f0(objectPtr);
}