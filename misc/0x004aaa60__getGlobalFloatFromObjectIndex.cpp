// FUNC_NAME: getGlobalFloatFromObjectIndex
// Function at 0x004aaa60: Retrieves a float value from a global engine table, indexed by a field from the input object.
// Uses thread-local storage (FS:[0x2C]) to access the engine instance, then follows pointer chain:
// TLS slot → engine pointer → engine+0x08 (likely a settings manager) → offset 0x6C (array base) + param1+0x18 (index).
// Returns the float at that position.

float __fastcall getGlobalFloatFromObjectIndex(int param1) // param1: some object (e.g., game entity) with an int index at +0x18
{
    // Access thread-local storage pointer from FS:[0x2C]
    // In standard Windows x86, FS:[0x2C] holds a pointer to the thread's TLS data block.
    // The first dereference yields the address of a static pointer variable (e.g., &gEngine),
    // the second dereference yields the actual engine pointer.
    int* tlsSlot = (int*)(__readfsdword(0x2C));             // *(int**) FS:0x2C
    int enginePtr = *(int*)(*tlsSlot);                     // **(int**) – engine instance address

    // enginePtr points to the global Engine object. At offset 0x08, there is a pointer to a settings/subsystem.
    int settingsPtr = *(int*)(enginePtr + 0x08);           // engine->settingsManager

    // The settings manager has a float array at offset 0x6C. The index into that array is stored at param1+0x18.
    int index = *(int*)(param1 + 0x18);                     // object->indexField (+0x18)
    int floatTableBase = settingsPtr + 0x6C;               // base of float array

    return *(float*)(floatTableBase + index);              // fetch float by index
}