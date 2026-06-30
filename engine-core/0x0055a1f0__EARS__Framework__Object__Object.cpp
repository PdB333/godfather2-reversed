// FUNC_NAME: EARS::Framework::Object::Object
// Address: 0x0055a1f0
// Role: Constructor for base Object class, initializes vtable pointers and default fields

extern uint32_t DAT_00e2b1a4;
extern uint32_t DAT_00e446bc;

class Object {
public:
    void* vtable;           // +0x00
    void* interfaceVtable;  // +0x04
    uint32_t someValue1;    // +0x08 (copied from DAT_00e2b1a4)
    uint32_t someValue2;    // +0x0C (copied from DAT_00e2b1a4)
    uint32_t someValue3;    // +0x10 (copied from DAT_00e446bc)
    uint32_t someValue4;    // +0x14 (copied from DAT_00e446bc)
    uint32_t someValue5;    // +0x18 (copied from DAT_00e446bc)
    uint32_t field_1C;      // +0x1C
    uint32_t field_20;      // +0x20
    uint32_t field_24;      // +0x24
    uint32_t field_28;      // +0x28
    uint32_t field_2C;      // +0x2C
    uint32_t field_30;      // +0x30
    uint32_t field_34;      // +0x34

    __thiscall Object() {
        vtable = (void*)0x00e3a038;          // PTR_FUN_00e3a038
        interfaceVtable = (void*)0x00e3a054; // PTR_LAB_00e3a054
        someValue1 = DAT_00e2b1a4;
        someValue2 = DAT_00e2b1a4;
        someValue3 = DAT_00e446bc;
        someValue4 = DAT_00e446bc;
        someValue5 = DAT_00e446bc;
        field_1C = 0;
        field_20 = 0;
        field_24 = 0;
        field_28 = 0;
        field_2C = 0;
        field_30 = 0;
        field_34 = 0;
    }
};