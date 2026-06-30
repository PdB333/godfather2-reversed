// FUNC_NAME: EARSObject::EARSObject
// Address: 0x005f7600
// Role: Constructor for a base EARS object. Calls internal initialization, then optionally performs cleanup based on a flag (likely memory management for dynamic/placement allocation).

uint32 __thiscall EARSObject::EARSObject(uint32 this, byte flags) {
    // Initialize base object (set vtable, reference count, etc.) via internal init function
    EARSObject::init(); // FUN_005f7620: internal initialization

    // If flag bit 0 is set, call a cleanup/destroy function (likely handles deletion of dynamically allocated memory)
    if ((flags & 1) != 0) {
        EARSObject::destroy(this); // FUN_009c8eb0: cleanup/destructor with memory deallocation
    }

    // Return the constructed object pointer
    return this;
}