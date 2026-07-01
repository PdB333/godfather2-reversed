// FUNC_NAME: EARSFrameworkObject::constructor
// Address: 0x00884e40
// Role: Constructor - initializes member fields and sets vtable

EARSFrameworkObject* __thiscall EARSFrameworkObject::EARSFrameworkObject(EARSFrameworkObject* this, undefined4 arg1, undefined4 arg2) {
    // Call base class constructor (FUN_004ac120)
    EARSFrameworkObjectBase::EARSFrameworkObjectBase(this, arg1, arg2);
    
    // Set vtable pointer
    this->vtable = &PTR_LAB_00d7702c;
    
    // Zero out various fields
    this->field_0x50 = 0; // +0x50 (param_1[0x14])
    this->field_0x54 = 0; // +0x54 (param_1[0x15])
    this->field_0x58 = 0; // +0x58 (param_1[0x16])
    this->field_0x60 = 0; // +0x60 (param_1[0x18])
    this->field_0x68 = 0; // +0x68 (param_1[0x1a])
    this->field_0x6C = 0; // +0x6C (param_1[0x1b])
    this->field_0x70 = 0; // +0x70 (param_1[0x1c])
    this->field_0x8C = 0; // +0x8C (param_1[0x23])
    this->field_0x9C = 0; // +0x9C (param_1[0x27])
    this->field_0xAC = 0; // +0xAC (param_1[0x2b])
    this->field_0x5C = 0; // +0x5C (param_1[0x17]) - set later
    this->field_0x64 = 0; // +0x64 (param_1[0x19]) - set later
    
    // Set field from global singleton or constant
    this->field_0xBC = g_globalField; // +0xBC (param_1[0x2f]) = _DAT_00d5780c
    
    return this;
}