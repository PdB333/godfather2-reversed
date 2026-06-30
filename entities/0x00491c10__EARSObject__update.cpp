// FUNC_NAME: EARSObject::update
// Function at address 0x00491c10
// Likely the main update/tick method for an EARS engine object. Checks for a non-null pointer at offset +0x1c0 (e.g., a sound handle or network packet) and if valid, calls a processing function with parameters from +0x14 (e.g., object ID) and +0x1d0 (e.g., data buffer). Then runs pre- and post-update routines.

void __fastcall EARSObject::update(int thisPtr) {
    // Pre-update work (e.g., input handling, state validation)
    FUN_00490b20();

    // If the pointer at +0x1c0 is non-null, process something
    if (*(int*)(thisPtr + 0x1c0) != 0) {
        // Call processing function:
        // - first param: value at +0x14 (likely an ID or handle)
        // - second param: the pointer from +0x1c0 (e.g., sound or network buffer)
        // - third param: buffer at +0x1d0 (e.g., output or state)
        FUN_0060ad20(
            *(undefined4*)(thisPtr + 0x14),  // +0x14: likely object ID or index
            *(int*)(thisPtr + 0x1c0),        // +0x1c0: non-null pointer to resource
            thisPtr + 0x1d0                  // +0x1d0: buffer or state data
        );
    }

    // Post-update work (e.g., animation blends, cleanup)
    FUN_00492190();
}