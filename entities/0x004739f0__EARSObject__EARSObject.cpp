// FUNC_NAME: EARSObject::EARSObject
undefined4 __thiscall EARSObject::EARSObject(byte allocFlag) {
    int *vtablePtr;
    
    // Call base class constructor (likely EARSBaseObject or similar)
    ConstructBase();  // FUN_00473a60
    
    // If the allocFlag bit 0 is set, allocate additional memory for the object
    if ((allocFlag & 1) != 0) {
        // Retrieve the class descriptor / vtable pointer for this type
        vtablePtr = (int *)GetClassDescriptor();  // FUN_009c8f80
        // Call the allocation routine through the vtable (offset +4) to allocate 0x60 (96) bytes
        (**(code (__thiscall **)(int, int))(*vtablePtr + 4))(this, 0x60);
    }
    
    return this;
}