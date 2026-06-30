// FUNC_NAME: EARSObject::~EARSObject
// Function address: 0x004de350
// Identified role: Destructor for EARSObject. Handles virtual cleanup of a member pointer at +0x4 and conditional deallocation.
void* __thiscall EARSObject::destructor(EARSObject* this, unsigned char deleteFlag) {
    // Set vtable to current class vtable (points to derived class's vtable)
    this->vtable = (void*)&PTR_FUN_00e36f1c; // +0x00

    // If the member pointer at offset +0x4 is not null, call its virtual function at vtable offset 0xC (index 3)
    if (this->someMemberPtr != nullptr) {
        // someMemberPtr is a pointer to another object; call its virtual destructor or cleanup
        (this->someMemberPtr->vtable[3])();
    }

    // Set vtable to base class vtable (prevents repeated virtual calls during destruction)
    this->vtable = (void*)&PTR_LAB_00e362b8; // +0x00

    // If the delete flag's LSB is set, deallocate the object via engine memory manager
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete (custom allocator)
    }

    return this;
}