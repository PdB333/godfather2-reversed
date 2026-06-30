// FUNC_NAME: EARSObject::release
// Function at 0x004b4280: Calls virtual cleanup at vtable+0x10, then deletion at vtable+0 with flag 1.
void EARSObject::release()
{
    // Call virtual function at offset 0x10 (likely shutdown/destroy)
    (**(void (**)())(*this + 0x10))();
    // Call virtual function at offset 0 (likely delete this) with argument 1
    (**(void (**)(int))*this)(1);
}