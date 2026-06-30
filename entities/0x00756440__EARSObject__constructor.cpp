// FUNC_NAME: EARSObject::constructor

// Constructor for a managed EARS object. Calls base initializer and optionally deletes on failure (flag bit 0).
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
    // Call base class constructor (likely sets vtable and zeroes fields)
    EARSObject::baseConstructor(); // FUN_00756270
    
    // If the low bit is set, clean up the object immediately (e.g., allocation failure)
    if (flags & 1) {
        this->~EARSObject(); // FUN_00624da0
    }
    
    return this;
}