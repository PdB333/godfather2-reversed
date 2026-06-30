// FUNC_NAME: EARSBaseObject::EARSBaseObject
// Address: 0x004689a0
// Constructor that sets up vtable pointers for EARS base object,
// calls the base class constructor, then adjusts vtable pointers
// for derived class (multiple inheritance) and resets a global flag.

void __fastcall EARSBaseObject::EARSBaseObject(void* this) // ecx = param_1
{
    // [this+0x00] – primary vtable pointer (base class)
    *(uint32_t*)this = (uint32_t)&VTable_Base;
    // [this+0x04] – secondary vtable pointer (e.g., for interface)
    *((uint32_t*)this + 1) = (uint32_t)&VTable_BaseSecondary;

    // Call base class constructor (common EARS initialization)
    FUN_0043e380(this);

    // Update vtable pointers after base construction (derived class)
    *((uint32_t*)this + 1) = (uint32_t)&VTable_DerivedSecondary;
    *(uint32_t*)this = (uint32_t)&VTable_DerivedPrimary;

    // Global flag (e.g., instance counter or singleton state)
    g_earsObjectCount = 0;
}