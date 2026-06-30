// FUNC_NAME: SimObject::SimObject(int)
// Address: 0x00703a20
// Role: Constructor for base SimObject class with multiple vtable pointers and class ID initialization.

__thiscall SimObject::SimObject(int arg) {
    // Call base class constructor
    FUN_0046c590(arg);

    // Assign vtable pointers (multiple inheritance)
    this->vtable0 = &PTR_FUN_00d60fa8; // Primary vtable at +0x00
    this->vtable1 = &PTR_LAB_00d60f98; // +0x3C
    this->vtable2 = &PTR_LAB_00d60f94; // +0x48
    this->vtable3 = &PTR_LAB_00d60f90; // +0x50 (overwrites earlier assignment to &PTR_LAB_00e32854)

    // Initialize fields
    this->field_0x54 = 0;        // +0x54
    *(uint16_t*)((uint8_t*)this + 0x58) = 0; // +0x58
    *(uint16_t*)((uint8_t*)this + 0x5A) = 0; // +0x5A

    this->field_0x5C = _DAT_00d578c0; // +0x5C (global value)

    this->field_0x60 = 0;        // +0x60

    // Byte fields
    *(uint8_t*)((uint8_t*)this + 0x64) = 0; // +0x64
    *(uint8_t*)((uint8_t*)this + 0x65) = 0; // +0x65
    *(uint8_t*)((uint8_t*)this + 0x66) = 0; // +0x66
    *(uint8_t*)((uint8_t*)this + 0x67) = 0xFF; // +0x67

    // Initialize class ID with debug markers (will be overwritten)
    this->field_0x68 = 0xBADBADBA; // +0x68
    this->field_0x6C = 0xBEEFBEEF; // +0x6C
    this->field_0x70 = 0xEAC15A55; // +0x70
    this->field_0x74 = 0x91100911; // +0x74

    // Retrieve actual class ID from a static function
    uint32_t* idPtr = FUN_0043ab10();
    this->field_0x68 = idPtr[0]; // Overwrite with real ID[0]
    this->field_0x6C = idPtr[1]; // Overwrite with real ID[1]
    this->field_0x70 = idPtr[2]; // Overwrite with real ID[2]
    this->field_0x74 = idPtr[3]; // Overwrite with real ID[3]

    // Returns this (implicit in assembly)
}