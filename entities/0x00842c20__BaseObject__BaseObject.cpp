// FUNC_NAME: BaseObject::BaseObject
BaseObject * __thiscall BaseObject::BaseObject(BaseObject *this, byte flags) {
    // Call base class constructor (FUN_00598d80)
    BaseObject::BaseConstruct(this);
    // Set vtable pointer to class-specific vtable (PTR_LAB_00d74620)
    this->vtable = (void **)0x00d74620;
    // If the object was allocated with flag bit 0 set, perform post-construction setup (FUN_00840230)
    if (flags & 1) {
        this->postConstruct(this);
    }
    return this;
}