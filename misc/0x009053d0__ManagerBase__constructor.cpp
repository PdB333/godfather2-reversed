// FUNC_NAME: ManagerBase::constructor
void __fastcall ManagerBase::constructor(ManagerBase* this)
{
    // Call base class constructor
    BaseClass::constructor(); // FUN_004c26c0

    // Set vtable pointer
    this->vtable = &PTR_FUN_00e36290;

    // Initialize fields at offsets 0x208, 0x20C, 0x210 to zero
    this->field_0x208 = 0; // param_1[0x82]
    this->field_0x20C = 0; // param_1[0x83]
    this->field_0x210 = 0; // param_1[0x84]
}