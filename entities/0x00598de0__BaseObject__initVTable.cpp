// FUNC_NAME: BaseObject::initVTable
void __thiscall BaseObject::initVTable(void)
{
    // Set the vtable pointer to the class's default vtable.
    // PTR_LAB_00e3b030 is a global pointer to the vtable structure.
    *reinterpret_cast<void**>(this) = &PTR_LAB_00e3b030;
}