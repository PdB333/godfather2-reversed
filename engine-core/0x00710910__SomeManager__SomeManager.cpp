// FUNC_NAME: SomeManager::SomeManager
// Address: 0x00710910
// Role: Constructor for a manager object (likely derived from EARS framework class)

SomeManager* __thiscall SomeManager::SomeManager(SomeManager* this, int param) {
    // Call base constructor at 0x0046c590
    FUN_0046c590(param);

    // Set vtable pointer at offset 0x00
    *this = (SomeManager*)&PTR_FUN_00d618f4;

    // Set function pointers at offsets +0x3C and +0x48
    this->field_0x3C = &PTR_LAB_00d618e4; // +0x3C
    this->field_0x48 = &PTR_LAB_00d618e0; // +0x48

    // Zero short fields: offsets 0x54, 0x56, 0x5C, 0x5E
    *(short*)(&this->field_0x54) = 0; // +0x54
    *(short*)((int)this + 0x56) = 0;  // +0x56
    *(short*)(&this->field_0x5C) = 0; // +0x5C
    *(short*)((int)this + 0x5E) = 0;  // +0x5E

    // Zero int fields: offsets 0x60, 0x64, 0x68, 0x6C
    this->field_0x60 = 0; // +0x60
    this->field_0x64 = 0; // +0x64
    this->field_0x68 = 0; // +0x68
    this->field_0x6C = 0; // +0x6C

    // Call static initialization function at 0x00710850
    int extraout_EDX = FUN_00710850();

    // Store the result in multiple fields: offsets 0x50, 0x58, 0x128
    this->field_0x50 = extraout_EDX;  // +0x50
    this->field_0x58 = extraout_EDX;  // +0x58
    this->field_0x128 = extraout_EDX; // +0x128

    return this;
}