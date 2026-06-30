// FUNC_NAME: SomeClass::SomeClass
int __thiscall SomeClass::SomeClass(int thisPtr, byte allocFlag)
{
    undefined4 *vtableSlot;

    // Set vtable pointer at offset 0x20 (class-specific vtable)
    if (thisPtr == 0) {
        vtableSlot = (undefined4 *)0x0;
    }
    else {
        vtableSlot = (undefined4 *)(thisPtr + 0x20);
    }
    *vtableSlot = &PTR_LAB_00d580e0;

    // Global initialization flag
    g_someGlobalFlag = 0; // DAT_011298ec

    // Subsystem initialization
    someInternalInit(); // FUN_007edfb0

    // If allocFlag bit 0 set, perform cleanup (e.g., free heap allocation)
    if ((allocFlag & 1) != 0) {
        someCleanup(thisPtr); // FUN_009c8eb0
    }

    return thisPtr;
}