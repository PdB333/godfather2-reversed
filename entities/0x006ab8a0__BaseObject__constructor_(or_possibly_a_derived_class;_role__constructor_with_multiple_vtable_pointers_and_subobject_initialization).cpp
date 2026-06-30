// FUNC_NAME: BaseObject::constructor (or possibly a derived class; role: constructor with multiple vtable pointers and subobject initialization)
void __thiscall BaseObject::constructor(BaseObject* this)
{
    // Set vtable pointer (offset +0x00)
    this->vtable = (VTableType*)&PTR_FUN_00d5da30;
    // Set additional vtable-like pointers at offsets +0x3C and +0x48
    this->field_0x3C = (int*)&PTR_LAB_00d5da20; // +0x3C
    this->field_0x48 = (int*)&PTR_LAB_00d5da1c; // +0x48

    // Initialize sub-objects at offsets +0x60, +0x50, +0x58
    // FUN_00408310 and FUN_004086d0 are likely constructors/destructors for internal members
    FUN_00408310(&this->field_0x60); // likely construct member at +0x60
    FUN_004086d0(&this->field_0x50); // likely destruct/reinit member at +0x50
    FUN_00408310(&this->field_0x50); // re-construct member at +0x50
    FUN_004086d0(&this->field_0x58); // destruct/reinit member at +0x58
    FUN_00408310(&this->field_0x58); // re-construct member at +0x58

    // Call the main constructor (likely base class or core logic)
    FUN_006abad0(this);

    // Check for a callback at offset +0x88; if non-null, invoke callback via pointer at +0x94
    if (this->field_0x88 != 0) {
        ((void (*)(void*))this->field_0x94)(this->field_0x88);
    }

    // Call a global initialization routine
    FUN_0046c640();
}