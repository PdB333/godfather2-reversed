// FUNC_NAME: EARSBaseObject::constructor
// Address: 0x004c3ff0
// Initializes the base object vtable pointers. Sets the primary vtable (+0x00) to a purecall table, 
// and the secondary vtable (+0x04) to a derived class vtable (two assignments, likely a base and 
// most-derived vtable for multiple inheritance; the last assignment persists).

void __fastcall EARSBaseObject::constructor(void* this)
{
    // Offset +0x04: pointer to secondary vtable (base class or second base)
    *(unsigned int*)((int)this + 4) = (unsigned int)&PTR_LAB_00e362e4;
    *(unsigned int*)((int)this + 4) = (unsigned int)&PTR_LAB_00e362b8;
    // Offset +0x00: primary vtable pointer (points to table with __purecall stubs)
    *(unsigned int*)this = (unsigned int)&PTR___purecall_00e30fac;
    return;
}