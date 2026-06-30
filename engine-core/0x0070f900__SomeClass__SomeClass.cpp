// FUNC_NAME: SomeClass::SomeClass
// Address: 0x0070f900
// Role: Constructor for SomeClass (object size likely 0x74)
// Sub-object at offset 0x50 (0x14 * 4) initialized via two base class constructors
// Additional table pointers stored at offsets 0x3C and 0x48

SomeClass::SomeClass(byte allocFlag)
{
    // Set primary vtable at offset 0x00
    *(void***)this = (void**)&PTR_FUN_00d618a4;

    // Set secondary table pointers at known offsets
    *(void**)((uint32_t)this + 0x3C) = &PTR_LAB_00d61894;  // +0x3C
    *(void**)((uint32_t)this + 0x48) = &PTR_LAB_00d61890;  // +0x48

    // Initialize sub-object at offset 0x50 (this + 0x14 words)
    void* subObject = (void*)((uint32_t)this + 0x50);
    FUN_004086d0(subObject);  // Base class constructor 1
    FUN_00408310(subObject);  // Base class constructor 2

    // Call global initialization routine
    FUN_0046c640();

    // If object was dynamically allocated, call allocation finalization with size
    if ((allocFlag & 1) != 0) {
        FUN_0043b960(this, 0x74);
    }
}