// FUNC_NAME: EARSObject::constructor

void __thiscall EARSObject::constructor(EARSObject *this) {
    undefined4 tempBuffer[4]; // temporary buffer for initialization
    void* vtablePointer = (void*)0x0062b6b0;
    
    // Set vtable pointer to the class-specific vtable
    *(void**)this = vtablePointer;
    
    // Call base class constructor
    FUN_006372d0();
    
    // Call initialization function with flags and buffer
    FUN_006371a0(this, 0, tempBuffer);
    
    return;
}