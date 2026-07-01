// FUNC_NAME: EARSObject::constructor
// Address: 0x007ca800
// Role: Constructor for a base EA EARS object (component with 8 fields, default constant 8 at +0x20)

class EARSObject {
public:
    void **vtable;      // +0x00 vtable pointer (set to PTR_LAB_00d6ea7c)
    int field_04;       // +0x04
    int field_08;       // +0x08
    char field_0C;      // +0x0C single byte
    int field_10;       // +0x10
    int field_14;       // +0x14
    int field_18;       // +0x18
    int field_1C;       // +0x1C
    int field_20;       // +0x20 initialized to 8 (max count / default size)

    // __thiscall constructor
    void __thiscall constructor() {
        this->vtable = (void**)&PTR_LAB_00d6ea7c;  // set vtable
        this->field_04 = 0;
        this->field_08 = 0;
        this->field_0C = 0;
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;
        this->field_20 = 8;   // default constant
    }
};