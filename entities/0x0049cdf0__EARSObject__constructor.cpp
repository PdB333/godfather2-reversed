// FUNC_NAME: EARSObject::constructor
undefined4* __thiscall EARSObject::constructor(undefined4* thisPtr, byte allocFlag) {
    int* allocatorPtr;
    
    // Set vtable pointer to this class's vtable (0x00e35238)
    *thisPtr = &PTR_FUN_00e35238;
    
    // Call base class constructor (likely EARSBaseObject or similar)
    // This initializes the base portion of the object.
    FUN_004bfcf0(); // BaseClass::constructor()
    
    // If the allocFlag has bit 0 set, we need to allocate memory and initialize
    if ((allocFlag & 1) != 0) {
        // Get the global memory allocator object (returns a pointer to an allocator instance)
        allocatorPtr = (int*)FUN_009c8f80(); // getGlobalAllocator()
        
        // Call the second virtual function (offset 4) of the allocator.
        // This function likely performs placement allocation/initialization for our object,
        // passing the object pointer and size (0xC0 = 192 bytes).
        (**(code**)(*allocatorPtr + 4))(thisPtr, 0xC0);
    }
    
    return thisPtr;
}