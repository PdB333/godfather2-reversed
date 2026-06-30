// FUNC_NAME: InstallMethodIntoTableAndCallConstructor

// Replaces a function pointer in an internal method table at offset +0x14 from the object's core data,
// advances the table pointer by 4 bytes, then calls the base constructor (FUN_004b9440) with the remaining parameters.
// This is likely used during object construction to patch a virtual dispatch table stored inside the object.

typedef void (*ConstructorFunc)(undefined4, undefined4, undefined8, undefined4);
extern void* PTR_FUN_011246b8; // global function pointer to be installed

void __thiscall InstallMethodIntoTableAndCallConstructor(int* thisPtr, undefined4 param1, undefined4 param2, undefined8 param3, undefined4 param4) {
    // The object's first field points to internal data (core object structure)
    int* coreData = reinterpret_cast<int*>(*thisPtr);

    // At offset +0x14 from coreData there is a pointer to a table of function pointers (method table)
    void*** methodTableSlot = reinterpret_cast<void***>(coreData + 0x14); // +0x14: method table pointer

    // Install the global function pointer into the current slot of that table
    **methodTableSlot = reinterpret_cast<void*>(&PTR_FUN_011246b8);

    // Advance the table pointer to the next slot (size of one function pointer = 4 bytes)
    *methodTableSlot = reinterpret_cast<void**>(reinterpret_cast<char*>(*methodTableSlot) + 4);

    // Delegate to the actual construction routine with the given parameters
    ((ConstructorFunc)FUN_004b9440)(param1, param2, param3, param4);
}