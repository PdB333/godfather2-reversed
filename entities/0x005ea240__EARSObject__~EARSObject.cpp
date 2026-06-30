// FUNC_NAME: EARSObject::~EARSObject
void* __thiscall EARSObject::~EARSObject(EARSObject* this, byte param_2)
{
    // Set vtable to first destructor vtable (likely derived class cleanup)
    *(void**)this = &PTR_FUN_00e36f1c;

    // If member at offset +0x4 is non-null, call its virtual destructor at vtable+0xc
    if ((int*)this->field_0x4 != (int*)nullptr)
    {
        (**(void (__thiscall**)(void*))((*((int*)this->field_0x4)) + 0xc))();
    }

    // Set vtable to second destructor vtable (likely base class)
    *(void**)this = &PTR_LAB_00e362b8;

    // If bit 0 of param_2 is set, deallocate memory
    if (param_2 & 1)
    {
        FUN_009c8eb0(this);
    }

    return this;
}