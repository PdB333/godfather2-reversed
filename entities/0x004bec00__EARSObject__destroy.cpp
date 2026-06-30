// FUNC_NAME: EARSObject::destroy
// Address: 0x004bec00
// This is a destroy/cleanup method that optionally deletes the object.
// The byte flag determines whether to free memory (bit 0 set = delete).
undefined4 __thiscall EARSObject::destroy(EARSObject* this, byte flag)
{
    // Perform internal cleanup (likely destructor body)
    this->cleanup(); // FUN_004bec20

    // If flag bit 0 is set, deallocate memory
    if ((flag & 1) != 0) {
        // Call operator delete on this object
        operator delete(this); // FUN_009c8eb0
    }

    return this;
}