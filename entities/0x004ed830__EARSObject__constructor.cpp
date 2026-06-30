// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(void* this, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10) {
    // this points to an object whose first member is a pointer to a structure (e.g., a VTable base)
    int* basePtr = *(int**)this;
    
    // Set the vtable pointer at offset +0x14 of that structure to a global vtable
    *(void**)(basePtr + 0x14) = &PTR_LAB_01124c74;
    
    // Advance the vtable pointer by 4 bytes (skip typeinfo or first entry)
    int* vtablePtr = (int*)(basePtr + 0x14);
    *vtablePtr = *vtablePtr + 4;
    
    // Forward call with param_4 replaced by 1 (likely a flag)
    FUN_004ee920(arg1, arg2, arg3, 1, arg5, arg6, arg7, arg8, arg9, arg10);
}