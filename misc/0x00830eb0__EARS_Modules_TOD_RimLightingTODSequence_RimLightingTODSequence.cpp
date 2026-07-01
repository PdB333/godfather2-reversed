// Xbox PDB: EARS_Modules_TOD_RimLightingTODSequence_RimLightingTODSequence
// FUNC_NAME: RimLightingTODSequence::constructor

// Address: 0x00830eb0
// Constructor for RimLightingTODSequence class (EA EARS engine).
// Initializes object with vtable pointer, sets some flags, loads a named data asset.

undefined4 * __fastcall RimLightingTODSequence::constructor(undefined4 *this)
{
    undefined4 uVar1;
    undefined1 *puVar2;
    int stackStruct[3];   // Temporary RAII object, possibly a ScopeGuard or ResourceContainer
    code *destructor;     // Function pointer to destroy the temporary object

    // Call base class constructor (likely some EARS base object)
    FUN_0082f5b0();

    // Set vtable pointer for RimLightingTODSequence
    *this = &PTR_FUN_00d739c8;

    // Set some flag: +0x24 (index 9) = 1
    this[9] = 1;

    // Load/create a named object "RimLightingTODSequence" (string ID or resource name)
    FUN_004d3bc0("RimLightingTODSequence");

    // Initialize a temporary RAII object on stack (likely a lock, ref counter, or scoped pointer)
    FUN_004d3e20(stackStruct);   // Sets up stackStruct and possibly destructor pointer

    // Get string from this[4] (member at offset +0x10), default to a hardcoded string if null
    puVar2 = (undefined1 *)this[4];
    if (puVar2 == (undefined1 *)0x0) {
        puVar2 = &DAT_0120546e;   // Default string constant (likely "default" or asset name)
    }

    // Load a data asset by name (streaming manager or data manager call)
    uVar1 = FUN_004dafd0(puVar2);
    this[3] = uVar1;   // Store loaded asset handle at +0x0C (index 3)

    // Clean up the temporary object: if its first field is non-zero, call destructor function
    if (stackStruct[0] != 0) {
        (*destructor)(stackStruct[0]);   // Release/destroy the temporary resource
    }

    return this;
}