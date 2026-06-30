// FUNC_NAME: Object::getVTable
// Address: 0x004959c0
// Returns the first DWORD of the object, typically the vtable pointer.
int __fastcall Object::getVTable(void)
{
    // Dereference the object pointer to get the vtable/type info at offset 0x00
    return *(int *)this;
}