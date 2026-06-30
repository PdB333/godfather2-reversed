// FUNC_NAME: UnknownClass::initDefaults
// Function at 0x0056f3c0: Initializes object fields with zeros and a global constant (likely a default value or handle).
// This appears to be a constructor or reset method for some EARS engine class.
void __fastcall UnknownClass::initDefaults(UnknownClass* this)
{
    // Global constant from address 0x00e2b1a4 (likely a sentinel or default value)
    int defaultVal = DAT_00e2b1a4;

    // First group: three zero ints at offsets 0x10-0x18, then default at 0x1c
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1c = defaultVal;

    // Second group: three zero ints at offsets 0x20-0x28, then default at 0x2c
    this->field_0x20 = 0;
    this->field_0x24 = 0;
    this->field_0x28 = 0;
    this->field_0x2c = defaultVal;

    // Four zero bytes at offsets 0x30-0x33
    *(int8_t*)((uintptr_t)this + 0x30) = 0;
    *(int8_t*)((uintptr_t)this + 0x31) = 0;
    *(int8_t*)((uintptr_t)this + 0x32) = 0;
    *(int8_t*)((uintptr_t)this + 0x33) = 0;

    // Subsequent fields zeroed out at offsets 0x34, 0x38, 0x3c, 0x40, 0x44
    this->field_0x34 = 0;
    this->field_0x38 = 0;
    this->field_0x3c = 0;
    this->field_0x40 = 0;
    this->field_0x44 = 0;
}