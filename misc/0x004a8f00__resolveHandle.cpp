// FUNC_NAME: resolveHandle
#include <cstdint>

// Handle lookup function at 0x004a8f00
// Checks if the handle ID is valid and then resolves the associated object.
// Called by many subsystems (audio, rendering, scripting, etc.) as a core engine utility.
int __fastcall resolveHandle(int *handleStruct)
{
    // Magic invalid handle sentinel: 0xFE16702F (signed -0x1E98FD1)
    const int INVALID_HANDLE = -0x1E98FD1; // -32063441

    int result = 0; // Return 0 (null) for invalid handles

    if (*handleStruct != INVALID_HANDLE) {
        // handleStruct[0] = handle ID, handleStruct[1] = auxiliary data (e.g., type, sub-index)
        result = internalLookup(*handleStruct, handleStruct[1]); // Calls FUN_004544a0
    }

    return result;
}