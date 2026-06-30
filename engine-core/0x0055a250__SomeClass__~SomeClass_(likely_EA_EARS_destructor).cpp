// FUNC_NAME: SomeClass::~SomeClass (likely EA EARS destructor)
// Function at 0x0055a250: Destructor with optional deletion flag
uint* __thiscall SomeClass::destructor(uint* this, byte deleting) {
    // Set vtable to current class vtable (offset +0x00 and +0x04)
    this[0] = (uint*)&PTR_FUN_00e3a038;   // vtable for this class
    this[1] = (uint*)&PTR_LAB_00e3a054;   // secondary vtable? (related to base class?)

    // If a child pointer at offset 0x34 (this[0xd]) is non-null, perform cleanup
    if (this[0xd] != 0) {
        FUN_009f1b20(this);   // likely deinitialize child or release resources
        FUN_009f01a0();       // global cleanup function (e.g., DeregisterObject)
    }

    // Restore base class vtable to purecall to prevent further virtual calls
    this[1] = (uint*)&PTR_LAB_00dc3dd4;   // some base vtable
    this[0] = (uint*)&PTR___purecall_00e3924c; // purecall vtable (crash on virtual call)

    // If deletion flag is set (bit 0), call operator delete on this
    if ((deleting & 1) != 0) {
        FUN_009c8eb0(this);   // likely operator delete(void*)
    }

    return this;
}