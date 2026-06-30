// FUNC_NAME: UnknownClass::constructor
// Function address: 0x006ae280
// Role: Constructor that sets vtable, destroys sub-object at offset +4 if present, and optionally deallocates itself if heap-allocated.

void* __thiscall UnknownClass::constructor(UnknownClass* this, bool isHeapAllocated)
{
    // If sub-object pointer at +0x4 is not null, destroy it
    if (this->subObjectPtr != nullptr) {
        FUN_004daf90(this->subObjectPtr); // destroySubObject
    }
    // Set class vtable pointer
    this->vtable = (void*)&PTR_LAB_00e2f0c0;
    // If heap-allocated, call deallocation routine on this
    if ((isHeapAllocated & 1) != 0) {
        FUN_009c8eb0(this); // deallocateThis
    }
    return this;
}