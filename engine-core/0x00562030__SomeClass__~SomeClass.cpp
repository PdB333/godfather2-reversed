// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::destructor(SomeClass* this) {
    // Set vtable to base class (likely a base destructor stub)
    *(uint32_t*)this = &PTR_FUN_00e3a428; // Base vtable?

    // +0x88: some pointer (maybe a sub-object or allocated resource)
    if (this->field_0x88 != 0) {
        FUN_009f01a0(); // Release/free resource
    }

    // +0x8C: pointer to a sub-object with its own vtable
    // +0x8C->+0x18: function pointer (likely destructor method)
    void (*subObjectDestructor)(int) = *(void (__thiscall**)(int))(this->field_0x8C + 0x18);
    this->field_0x88 = 0;
    subObjectDestructor(0); // Call sub-object destructor with 0 (maybe a flag)
    this->field_0x8C = &PTR_FUN_00e3a038; // Set sub-object vtable to a stub
    this->field_0x90 = &PTR_LAB_00e3a054; // Another vtable/SOMETHING

    // +0xC0: another optional sub-object
    if (this->field_0xC0 != 0) {
        FUN_009f1b20(&this->field_0x8C); // Clean up sub-object at +0x8C
        FUN_009f01a0(); // Release/free resource
    }

    // Final vtable assignments to purecall stubs (ensures no further vtable calls)
    this->field_0x90 = &PTR_LAB_00dc3dd4;
    this->field_0x8C = &PTR___purecall_00e3924c;
}