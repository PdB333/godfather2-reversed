// FUNC_NAME: GhostObject::GhostObject (constructor, address 0x00475830)
// Initializes a GhostObject with vtable pointers, debug signature markers, and clears fields.

void __thiscall GhostObject::GhostObject(void* arg) {
    // Call base class constructor at 0x0046c590
    FUN_0046c590(arg);

    // Set primary vtable pointer
    this->vtable = (void*)&PTR_FUN_00e32e14;

    // Set secondary vtable pointers (likely for multiple inheritance or interface)
    // +0x3C: first derived vtable
    this->subVtable1 = (void*)&PTR_LAB_00e32e30;
    // +0x48: second derived vtable
    this->subVtable2 = (void*)&PTR_LAB_00e32e40;

    // Initialize signature fields with distinctive patterns (debug guards)
    // +0x50: first magic number
    this->magic1 = 0xBADBADBA;  // "BAD BAD BA"
    // +0x54: second magic number
    this->magic2 = 0xBEEFBEEF;  // "BEEF BEEF"
    // +0x58: third magic number
    this->magic3 = 0xEAC15A55;  // Possibly EA EARS identifier
    // +0x5C: fourth magic number
    this->magic4 = 0x91100911;  // Unique marker

    // Clear all magic numbers and other fields to zero (indicates object is constructed)
    // Done in reverse order as per assembly
    this->magic4 = 0;
    this->magic3 = 0;
    this->magic2 = 0;
    this->magic1 = 0;
    // +0x68: clear field
    this->field2 = 0;
    // +0x6C: clear field
    this->field3 = 0;
    // +0x60: clear field
    this->field0 = 0;
    // +0x64: clear field
    this->field1 = 0;
}