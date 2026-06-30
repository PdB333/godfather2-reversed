// FUNC_NAME: EARSObject::destroy
void __fastcall EARSObject::destroy(int this)
{
    // Call global deallocation function (likely memory manager)
    FUN_009f2000();

    // Call virtual destructor or cleanup function from vtable
    // Object has a pointer at +0xD0 to a structure (maybe vtable or function table)
    // At offset 0x4C of that structure is a function pointer to call
    (**(code **)(*(int *)(this + 0xD0) + 0x4C))();
}