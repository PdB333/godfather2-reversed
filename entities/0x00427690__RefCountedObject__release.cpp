// FUNC_NAME: RefCountedObject::release
void __thiscall RefCountedObject::release(void)
{
    // Call Release on the first interface pointer stored at +0x48, with parameter 0 (likely final release flag)
    (*(this->vtable + 1))(this->field_0x48, 0);

    // If the second interface pointer at +0x54 is non-null, release it as well
    if (this->field_0x54 != 0) {
        (*(this->vtable + 1))(this->field_0x54, 0);
    }

    // Call the virtual destructor at vtable offset 0xc (index 3)
    (*(this->vtable + 3))(this);
}