// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte flags) {
    // Call base class constructor (likely EARSObject base or another parent)
    FUN_008b6d20(); // assumed: BaseClass::constructor(this)
    
    // If the lowest bit of flags is set, deallocate memory for this object
    if ((flags & 1) != 0) {
        // Sized deallocation: operator delete(this, 0x2d0) or custom memory manager
        FUN_0043b960(this, 0x2d0); // 0x2d0 = 720 bytes (class size)
    }
    
    return this;
}