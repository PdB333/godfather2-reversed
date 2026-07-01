// FUNC_NAME: SomeClass::Constructor
// Reconstructed constructor at 0x007ec2a0
// Initializes member variables and sets vtable pointer
class SomeClass {
public:
    void* vtable;          // +0x00
    int field_04;          // +0x04 (param_2)
    int field_08;          // +0x08 (param_5)
    int field_0C;          // +0x0C (init 0)
    short field_10;        // +0x10 (2 bytes)
    short field_12;        // +0x12 (2 bytes)
    int field_14;          // +0x14 (param_4)
    int field_18;          // +0x18 (init 0)
};

SomeClass* __thiscall SomeClass::Constructor(SomeClass* this, int arg1, int arg2, int arg3, int arg4) {
    this->vtable = &PTR_FUN_00d6ffac; // vtable address
    this->field_04 = arg1;
    this->field_08 = arg4;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_12 = 0;
    this->field_14 = arg3;
    this->field_18 = 0;
    FUN_004080d0(arg2); // likely a base constructor or initializer
    this->field_18 = 0;
    return this;
}