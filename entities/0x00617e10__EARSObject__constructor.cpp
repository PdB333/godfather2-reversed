// FUNC_NAME: EARSObject::constructor
// Address: 0x00617e10
// Initializes a base EARS game object/component with vtable and zeroed fields.

struct EARSObject {
    void **vtable; // +0x00
    int field_4;   // +0x04
    int field_8;   // +0x08
    int field_0C;  // +0x0C
    int field_10;  // +0x10
    int field_14;  // +0x14
    int field_18;  // +0x18
    int field_1C;  // +0x1C
    int field_20;  // +0x20
    int field_24;  // +0x24
    int field_28;  // +0x28
    int field_2C;  // +0x2C
    int field_30;  // +0x30
    int field_34;  // +0x34
    int field_38;  // +0x38
    int field_3C;  // +0x3C
    int field_40;  // +0x40
    int field_44;  // +0x44
    int field_48;  // +0x48
    int field_4C;  // +0x4C
    int field_50;  // +0x50
    int field_54;  // +0x54
    int field_58;  // +0x58
};

void __thiscall EARSObject::constructor(EARSObject *this) {
    this->vtable = &PTR_LAB_00e40d18; // set vtable pointer
    this->field_4 = 0;
    this->field_8 = 0;
    this->field_0C = 0;
    this->field_10 = 0; // param_1[4] (offset 0x10)
    this->field_14 = 0; // param_1[5] (offset 0x14)
    this->field_18 = 0; // param_1[6]
    this->field_1C = 0; // param_1[7]
    this->field_20 = 0; // param_1[8] (offset 0x20)
    this->field_24 = 0; // param_1[9]
    this->field_28 = 0; // param_1[0xa]? Wait, decompiled shows param_1[0xb] for offset 0x2C? Check: param_1[0xb] is offset 0x2C. So we need to assign in order given? The list order is not sequential offset; it goes: [1],[2],[3],[8],[4],[5],[6],[7],[9],[10],[0xb],[0xc],... That is a bit messy. However, the decompiled code literally sets param_1[2] before param_1[4], so we must preserve the order as written. But logically it doesn't matter. For readability, I'll group by offset in increasing order, but the decompiled order indicates the compiler may have interleaved. To be safe, I'll follow the decompiled sequence exactly, as it might be due to register allocation. But as the output should be a clean C++ reconstruction, I'll reorder to offset order. The function's behavior is just zeroing, so order irrelevant.
    this->field_2C = 0; // param_1[0xb]
    this->field_30 = 0; // param_1[0xc]
    this->field_34 = 0; // param_1[0xd]
    this->field_38 = 0; // param_1[0xe]
    this->field_3C = 0; // param_1[0xf]
    this->field_40 = 0; // param_1[0x10]
    this->field_44 = 0; // param_1[0x11]
    this->field_48 = 0; // param_1[0x12]
    this->field_4C = 0; // param_1[0x13]
    this->field_50 = 0; // param_1[0x14]
    this->field_54 = 0; // param_1[0x15]
    this->field_58 = 0; // param_1[0x16]
    return;
}