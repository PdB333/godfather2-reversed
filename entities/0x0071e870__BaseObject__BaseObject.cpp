// FUNC_NAME: BaseObject::BaseObject
void __thiscall BaseObject::BaseObject(BaseObject *this)
{
    // Set the vtable pointer to the base class vtable
    *reinterpret_cast<void**>(this) = &PTR_LAB_00d61e58; // +0x00: vtable pointer
}