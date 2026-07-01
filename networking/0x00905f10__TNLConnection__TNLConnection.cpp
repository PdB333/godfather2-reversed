// FUNC_NAME: TNLConnection::TNLConnection
void __fastcall TNLConnection::TNLConnection(TNLConnection *this)
{
    // Set vtable pointer for this class (first entry)
    this->vtable = &VTABLE_00d826c8; // +0x00: vtable for TNLConnection
    // Set additional vtable pointers for base classes or interfaces
    this->field_3C = &VTABLE_00d826b8; // +0x3C: vtable for first base class
    this->field_48 = &VTABLE_00d826b4; // +0x48: vtable for second base class
    this->field_50 = &VTABLE_00d826b0; // +0x50: vtable for another base (will be overwritten later)
    // Construct sub-object at offset 0x58 (likely a base class data block)
    FUN_004086d0(&this->subObject_58); // +0x58: Initialize first part of sub-object
    FUN_00408310(&this->subObject_58); // +0x58: Finalize sub-object (constructor chain)
    // Overwrite the vtable pointer at +0x50 after base construction
    this->field_50 = &VTABLE_00e32854; // +0x50: Updated vtable for derived class override
    // Call static initialization for session-related globals
    FUN_0046c640(); // Initialize net session static data
}