// FUNC_NAME: BaseClassWithTwoPtrs::~BaseClassWithTwoPtrs

void __thiscall BaseClassWithTwoPtrs::~BaseClassWithTwoPtrs(BaseClassWithTwoPtrs* this) {
    // Release member at +0x0C if non-null
    if (this->field_0x0C != nullptr) {
        releaseObject(this->field_0x0C);  // FUN_004daf90
    }
    // Release member at +0x04 if non-null
    if (this->field_0x04 != nullptr) {
        releaseObject(this->field_0x04);  // FUN_004daf90
    }
    // Restore vtable pointer to base class static vtable
    this->vtable = &PTR_LAB_00e2f0c0;
}