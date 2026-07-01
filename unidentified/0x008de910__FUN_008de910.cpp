// FUNC_NAME: SomeClass::SomeClass
// Address: 0x008de910
// Role: Constructor for a class with multiple vtable pointers (multiple inheritance or interface implementation)
// Base constructor called: FUN_008ded10

SomeClass* SomeClass::SomeClass(undefined4 someParameter) {
    // Call base class constructor
    FUN_008ded10(someParameter);

    // Set primary vtable
    this->vtable = &PTR_FUN_00d7ef20;

    // Set additional interface/vtable pointers
    // +0x3C (offset 0xf)
    this->interface1 = &PTR_LAB_00d7ef10;
    // +0x48 (offset 0x12)
    this->interface2 = &PTR_LAB_00d7ef0c;
    // +0x50 (offset 0x14)
    this->interface3 = &PTR_LAB_00d7ef08;
    // +0x54 (offset 0x15)
    this->interface4 = &PTR_LAB_00d7eea8;
    // +0x58 (offset 0x16)
    this->interface5 = &PTR_LAB_00d7ee40;
    // +0x210 (offset 0x84)
    this->somePointer = 0;

    return this;
}