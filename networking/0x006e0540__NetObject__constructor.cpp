// FUNC_NAME: NetObject::constructor
// Address: 0x006e0540
// Role: Constructor for a derived class (likely NetObject or similar) with multiple vtable pointers.
// Initializes base class, sets up virtual function table pointers at offsets 0x00, 0x3C, 0x48, 0x50,
// and zeros out fields at offsets 0x58, 0x5C, 0x60, 0x64.

void * __fastcall NetObject::constructor(NetObject *this) // __fastcall: this in ecx, no edx used
{
    // Call base class constructor (actual base class unknown)
    BaseClass::constructor(); // FUN_004737b0

    // Set primary vtable pointer at offset 0x00
    this->vtable = (void**)&VTBL_NetObject; // PTR_FUN_00d5f758

    // Set secondary vtable pointer at offset 0x3C (index 0xF)
    // This is likely for an additional interface or base class
    this->vtable_secondary_0x3C = (void**)&VTBL_InterfaceA; // PTR_LAB_00d5f748

    // Set another vtable pointer at offset 0x48 (index 0x12)
    this->vtable_secondary_0x48 = (void**)&VTBL_InterfaceB; // PTR_LAB_00d5f744

    // Set another vtable pointer at offset 0x50 (index 0x14)
    this->vtable_secondary_0x50 = (void**)&VTBL_InterfaceC; // PTR_LAB_00d5f740

    // Zero out member fields at offsets 0x58, 0x5C, 0x60, 0x64
    this->field_0x58 = nullptr; // param_1[0x16]
    this->field_0x5C = nullptr; // param_1[0x17]
    this->field_0x60 = nullptr; // param_1[0x18]
    this->field_0x64 = nullptr; // param_1[0x19]

    // Additional initialization
    NetObject::initialize(); // FUN_006e01d0

    return this;
}