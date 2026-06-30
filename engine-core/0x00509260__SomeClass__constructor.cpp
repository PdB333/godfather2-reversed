// FUNC_NAME: SomeClass::constructor
// Function address: 0x00509260
// Role: Constructor for a class with vtable at 0x00e37930. Initializes fields to default values and increments reference count of a passed object.

void SomeClass::constructor(void* objPtr) // objPtr in EAX, this in ESI (non-standard)
{
    int* refCountObj;
    int defaultVal = DAT_00e2b1a4; // Global default value

    // Set vtable pointer
    this->vtable = &PTR_FUN_00e37930;

    // Initialize fields
    this->field_4 = 0;          // +0x04
    this->field_20 = 0;         // +0x20 (index 8)
    this->field_24 = 0;         // +0x24 (index 9)
    this->field_28 = 0;         // +0x28 (index 10)
    this->field_2C = defaultVal; // +0x2C (index 0xB)
    this->field_30 = defaultVal; // +0x30 (index 0xC)
    this->field_34 = defaultVal; // +0x34 (index 0xD)
    this->field_38 = 0;         // +0x38 (index 0xE)

    // Set array fields to default value
    this->field_10[0] = defaultVal; // +0x10 (index 4)
    this->field_10[1] = defaultVal; // +0x14 (index 5)
    this->field_10[2] = defaultVal; // +0x18 (index 6)
    this->field_10[3] = defaultVal; // +0x1C (index 7)

    // Dereference objPtr to get the object whose reference count to increment
    refCountObj = *(int**)objPtr;
    if (refCountObj != 0) {
        // Increment reference count at offset +0x04
        *(int*)((char*)refCountObj + 4) += 1;
    }

    // Call another initialization function with the object pointer
    FUN_00509350(refCountObj);
}