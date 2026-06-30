// FUNC_NAME: SomeManager::constructor
// Address: 0x006bdf50
// This is a constructor for an object with vtable at 0x00d5eaec.
// It initializes two function pointer slots at +0x3C and +0x48,
// constructs a sub-object at +0x80, calls a global init, and
// handles heap allocation based on a flag (bit 0).

SomeManager* __thiscall SomeManager::constructor(SomeManager* this, byte allocationFlag)
{
    // Set virtual function table pointer (offset +0x00)
    this->vtable = &PTR_FUN_00d5eaec;

    // Set function pointers at known offsets
    this->field_0x3C = &PTR_LAB_00d5eadc;   // +0x3C
    this->field_0x48 = &PTR_LAB_00d5ead8;   // +0x48

    // Construct sub-object at offset +0x80 (this + 0x20 in uint* arithmetic)
    // FUN_004086d0 is presumably the constructor for this sub-object
    FUN_004086d0(this + 0x20);
    // FUN_00408310 likely performs additional initialization (e.g., reset or setup)
    FUN_00408310(this + 0x20);

    // Global initialization routine (possibly static factory or manager init)
    FUN_006bcd70();

    // If allocation flag has bit 0 set, perform cleanup/release for heap-allocated object
    if ((allocationFlag & 1) != 0) {
        FUN_0043b960(this, 0x98);   // 0x98 = total object size (in bytes)
    }

    return this;
}