// FUNC_NAME: EARSObject::EARSObject

void* __thiscall EARSObject::EARSObject(byte isNew) {
    // Set the virtual function table pointer (VFT)
    this->vtable = &EARSObject::vtable; // +0x00: vtable pointer (address 0x00d7c520)
    // Call base class constructor (likely Object or EARSBase at 0x004149b0)
    BaseEARSObject::BaseEARSObject();
    // If the object was allocated via operator new ('isNew' flag), call additional
    // initialization/allocator-specific setup (function at 0x009c8eb0)
    if (isNew & 1) {
        this->postNewInit(); // e.g., register, enable reflection, etc.
    }
    return this;
}