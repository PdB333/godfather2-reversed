// FUNC_NAME: SomeManager::constructor
undefined4 * __fastcall SomeManager::constructor(undefined4 *thisPtr)
{
    undefined4 uVar1;

    // Call base class constructor (likely sets first vtable and base fields)
    FUN_005bf9b0();

    uVar1 = DAT_00d916a4; // Save a global value for later assignment

    // Set vtable pointers for multiple interfaces
    thisPtr[0x13] = &PTR_LAB_00d91594; // +0x4C first vtable assignment
    DAT_0112992c = thisPtr; // Store singleton pointer globally (instance of this class)

    // Zero-initialize various fields
    *(undefined1 *)(thisPtr + 0x14) = 0; // +0x50 byte field
    thisPtr[0x15] = 0; // +0x54
    *(undefined1 *)(thisPtr + 0x16) = 0; // +0x58 byte field
    thisPtr[0x17] = 0; // +0x5C
    thisPtr[0x18] = 0; // +0x60

    // Set vtable pointers (main and base classes)
    *thisPtr = &PTR_FUN_00d915d8;      // +0x00 main vtable
    thisPtr[4] = &PTR_LAB_00d915b0;    // +0x10 second vtable
    thisPtr[0x13] = &PTR_LAB_00d915ac; // +0x4C override (likely derived vtable)
    thisPtr[0x19] = 0; // +0x64
    thisPtr[0x1a] = 0; // +0x68
    thisPtr[0x1b] = 0; // +0x6C
    thisPtr[0x1c] = 0; // +0x70

    // Set pointer to a manager or config (e.g., property list)
    thisPtr[0x1d] = &PTR_LAB_00d83b18; // +0x74

    // Assign from global values (likely other managers or constants)
    thisPtr[0x3e] = uVar1;  // +0xF8
    thisPtr[0x3f] = DAT_00d5f414; // +0xFC

    return thisPtr;
}