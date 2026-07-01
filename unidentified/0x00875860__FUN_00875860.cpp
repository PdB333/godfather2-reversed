// FUNC_NAME: BaseClass::~BaseClass
void __thiscall BaseClass::~BaseClass(BaseClass* this)
{
    // Clean up pointer at offset +0xC (likely a child object or resource)
    if (this->field_0xC != 0) {
        FUN_004daf90(&this->field_0xC); // Deallocation function (e.g., operator delete)
    }
    // Clean up pointer at offset +0x4 (another child object or resource)
    if (this->field_0x4 != 0) {
        FUN_004daf90(&this->field_0x4);
    }
    // Restore vtable pointer to base class vtable (for base destructor chaining)
    this->vtable = &PTR_LAB_00e2f0c0;
}