// FUNC_NAME: ObjectBase::constructor
void __fastcall ObjectBase::constructor(ObjectBase *this)
{
    // Set vtable pointer at offset 0x00 to the class's vtable
    this->vtable = &PTR_LAB_00d6ea7c;
    return;
}