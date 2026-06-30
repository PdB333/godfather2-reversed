// FUNC_NAME: BaseObject::BaseObjectConstructor
// Address: 0x004dfd00
// Role: Base class constructor/destructor hybrid (param_2 flags: bit 0 = deallocate on destruction)
// Sets vtable and initializes member at +0xC with two successive assignments (bug? intentional?).
// Resets global g_baseObjectCount to 0 and calls initSubsystem().

// Known from Xbox debug build: likely part of EARS::Framework or EARS::Modules base hierarchy.

undefined4* __thiscall BaseObject::constructor(BaseObject* thisPtr, byte flags) {
    // Set vtable pointer at offset 0x00
    thisPtr->vtable = &PTR_FUN_00e36f5c;
    
    // Initialize member at offset 0x0C (first with a pointer, then overwritten)
    // This might be a union or a two-step initialization for derived classes.
    thisPtr[3] = (undefined4*)&PTR_LAB_00e36f6c;
    thisPtr[3] = (undefined4*)&PTR_LAB_00e36f70;
    
    // Global count reset (likely for debugging or initialization tracking)
    g_baseObjectCount = 0; // DAT_012234c4
    
    // Call subsystem initialization (e.g., register with manager)
    FUN_004083d0(); // initSubsystem()
    
    // If flag bit 0 is set, deallocate memory (likely operator delete)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(thisPtr); // operator delete(thisPtr)
    }
    
    return thisPtr;
}