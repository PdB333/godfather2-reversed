// FUNC_NAME: Object::Object
// Reconstructed constructor for a base EARS object class
// Sets vtable pointer and zeroes initial fields
// 
// Note: param_1 is the 'this' pointer passed in ecx (__thiscall, not __fastcall as Ghidra suggests)
// Vtable pointer is at +0x00, byte flag at +0x1C, 6 DWORDs from +0x04 to +0x18 are zeroed

struct Object {
    void** vtable;       // +0x00
    int field_04;       // +0x04
    int field_08;       // +0x08
    int field_0C;       // +0x0C
    int field_10;       // +0x10
    int field_14;       // +0x14
    int field_18;       // +0x18
    uint8_t byte_1C;    // +0x1C
};

void __fastcall Object::Object(Object* this) {
    // Set vtable pointer from global data section
    this->vtable = &PTR_LAB_00d60cdc;  // presumably a class-specific vtable
    
    // Zero all scalar fields
    this->field_04 = 0;
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->byte_1C = 0;
    
    return;
}