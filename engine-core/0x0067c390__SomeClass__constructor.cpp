// FUNC_NAME: SomeClass::constructor
struct SomeClass {
    void** vtable; // +0x00
    int somePointer; // +0x04
    char byteField1; // +0x08
    char byteField2; // +0x09
    char byteField3; // +0x0A
    char byteField4; // +0x0B
    // padding 0x0C-0x12
    char byteField5; // +0x13
};

extern void* SomeClass_vtable; // 0x00d57728

void __thiscall SomeClass::constructor(SomeClass* this, int param_2) {
    this->vtable = &SomeClass_vtable;
    this->somePointer = param_2;
    this->byteField1 = 0;
    this->byteField2 = 0;
    this->byteField3 = 0;
    this->byteField4 = 0;
    this->byteField5 = 0;
}