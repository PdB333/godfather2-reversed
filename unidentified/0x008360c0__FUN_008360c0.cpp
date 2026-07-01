//FUNC_NAME: SomeClass::initializeWithScale
// Address: 0x008360c0
// Role: Initializes object with scaled values from source data (5 floats at offsets 0x4c-0x5c)

class SomeClass {
public:
    // Vtable pointer at offset 0x00
    // Fields at offsets 0x4c, 0x50, 0x54, 0x58, 0x5c (5 floats)
    // ...
    SomeClass* initializeWithScale(float scale, int* sourceData);
};

SomeClass* SomeClass::initializeWithScale(float scale, int* sourceData) {
    // Call base class initializer (likely constructor or common init)
    FUN_008334a0();

    // Set vtable pointer
    this->vtable = &PTR_LAB_00d7377c;

    // Load default values from globals (overwritten below)
    this->field_0x4c = DAT_00d5ef88;
    this->field_0x58 = DAT_00e44630;
    this->field_0x50 = DAT_00d6471c;
    this->field_0x54 = _DAT_00d5cf70;
    this->field_0x5c = _DAT_00d5cf70;

    // Overwrite with scaled values from source data (offsets 0x4c-0x5c)
    this->field_0x4c = *(float*)(sourceData + 0x4c) * scale;
    this->field_0x50 = *(float*)(sourceData + 0x50) * scale;
    this->field_0x54 = *(float*)(sourceData + 0x54) * scale;
    this->field_0x58 = *(float*)(sourceData + 0x58) * scale;
    this->field_0x5c = *(float*)(sourceData + 0x5c) * scale;

    return this;
}