// FUNC_NAME: EARSObject::~EARSObject
void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
    // Set vtable pointer for this class (base class vtable)
    *this = &PTR_FUN_00d5fe50; // +0x00: vtable for EARSObject
    // Set vtable pointers for multiple inheritance base classes
    this[0xf] = &PTR_LAB_00d5fe40; // +0x3C: base class A vtable
    this[0x12] = &PTR_LAB_00d5fe3c; // +0x48: base class B vtable

    // Destroy sub-object at offset 0x14 (byte offset 0x50)
    // Typically a contained object (e.g., string, list)
    releaseSubObject(this + 0x14);   // FUN_004086d0
    finalizeSubObject(this + 0x14); // FUN_00408310

    // Destroy owned object pointers in reverse order of allocation
    // Each pointer has a destructor function stored at offset +3 (e.g., vtable + 0)
    if (this[0x2e] != NULL) {
        ((void (*)(void *))this[0x31])(this[0x2e]); // call destructor on object at +0xB8
    }
    if (this[0x2a] != NULL) {
        ((void (*)(void *))this[0x2d])(this[0x2a]); // +0xA8
    }
    if (this[0x26] != NULL) {
        ((void (*)(void *))this[0x29])(this[0x26]); // +0x98
    }
    if (this[0x22] != NULL) {
        ((void (*)(void *))this[0x25])(this[0x22]); // +0x88
    }
    if (this[0x1e] != NULL) {
        ((void (*)(void *))this[0x21])(this[0x1e]); // +0x78
    }
    if (this[0x1a] != NULL) {
        ((void (*)(void *))this[0x1d])(this[0x1a]); // +0x68
    }

    // Final cleanup (debug logging, memory pool, etc.)
    globalCleanup(); // FUN_0046c640
}