// FUNC_NAME: EARSBaseObject::EARSBaseObject
struct EARSBaseObject {
    // vtable pointers and data at known offsets
};

void * __thiscall EARSBaseObject::EARSBaseObject(EARSBaseObject *this, unsigned int param_2)
{
    // Base class constructor call – likely initializes base (e.g., ObjectBase, 0x0046c590)
    FUN_0046c590(param_2);

    // Set vtable pointers and interface tables
    // +0x50: pointer to another vtable (LAB_00e32854) – probably secondary vtable or interface
    *(void **)((char *)this + 0x50) = (void *)&PTR_LAB_00e32854;
    // +0x00: primary vtable (FUN_00e32b30)
    *(void **)this = (void *)&PTR_FUN_00e32b30;
    // +0x3C: pointer to another vtable (LAB_00e32b50)
    *(void **)((char *)this + 0x3C) = (void *)&PTR_LAB_00e32b50;
    // +0x48: pointer to another vtable (LAB_00e32b60)
    *(void **)((char *)this + 0x48) = (void *)&PTR_LAB_00e32b60;
    // +0x50: overwritten with different vtable (LAB_00e32b64) – possibly final assignment for multiple inheritance
    *(void **)((char *)this + 0x50) = (void *)&PTR_LAB_00e32b64;

    return this;
}