// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x00902310
// Destructor for an object of size 0x70 bytes.
// Calls base destructor (FUN_00902120) and conditionally frees memory.

void __thiscall EARSObject::~EARSObject(byte deleteFlag) {
    // Call base class destructor (at 0x00902120)
    baseDestructor();
    // If deleteFlag has bit 0 set, deallocate memory
    if (deleteFlag & 1) {
        // operator delete with object size 0x70 (at 0x0043b960)
        operatorDelete(this, 0x70);
    }
}