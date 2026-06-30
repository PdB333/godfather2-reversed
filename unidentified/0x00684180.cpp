// FUN_00684180: SomeEntity::constructor

struct SomeEntity {
    void** vtable;          // +0x00
    // ... other members up to 0x94 bytes total
    void* field_0x3C;       // +0x3C
    void* field_0x48;       // +0x48
    // likely additional fields
};

__thiscall undefined4* SomeEntity::constructor(SomeEntity* this, byte param_2)
{
    this->vtable = &PTR_FUN_00d588bc;
    this->field_0x3C = &PTR_LAB_00d588ac;
    this->field_0x48 = &PTR_LAB_00d588a8;
    FUN_0078ecf0();                      // base class constructor
    this->vtable = &PTR_FUN_00d5888c;
    this->field_0x3C = &PTR_LAB_00d5887c;
    this->field_0x48 = &PTR_LAB_00d58878;
    FUN_0046c640();                      // derived class initializer
    if ((param_2 & 1) != 0) {           // if allocated flag is set
        FUN_0043b960(this, 0x94);       // typically operator delete with size
    }
    return this;
}