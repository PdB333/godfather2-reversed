// FUNC_NAME: SomeObject::constructor
// Function address: 0x00748570
// Role: Constructor for an object with vtable at 0x00d6415c.
// Initializes base class and zeroes multiple fields.

void __thiscall SomeObject::constructor(SomeObject* this, int param2, int param3) {
    // Call base class constructor (likely an EARS framework base)
    BaseClass::constructor(this, param2, param3);

    // Set vtable pointer
    this->vtable = (void*)0x00d6415c;

    // Zero out 4-byte fields at offsets +0x58 through +0x74
    this->field_0x58 = 0; // +0x58 (index 0x16)
    this->field_0x5C = 0; // +0x5C (index 0x17)
    this->field_0x60 = 0; // +0x60 (index 0x18)
    this->field_0x64 = 0; // +0x64 (index 0x19)
    this->field_0x68 = 0; // +0x68 (index 0x1A)
    this->field_0x6C = 0; // +0x6C (index 0x1B)
    this->field_0x70 = 0; // +0x70 (index 0x1C)
    this->field_0x74 = 0; // +0x74 (index 0x1D)

    // Zero out 8-byte fields at offsets +0x78 through +0xA0 (6 fields)
    this->field_0x78 = 0; // +0x78 to +0x7F (index 0x1E)
    this->field_0x80 = 0; // +0x80 to +0x87 (index 0x20)
    this->field_0x88 = 0; // +0x88 to +0x8F (index 0x22)
    this->field_0x90 = 0; // +0x90 to +0x97 (index 0x24)
    this->field_0x98 = 0; // +0x98 to +0x9F (index 0x26)
    this->field_0xA0 = 0; // +0xA0 to +0xA7 (index 0x28)

    // Zero a single byte at offset +0xA8 (index 0x2A)
    this->field_0xA8 = 0; // byte field
}