// FUNC_NAME: UnknownClass::constructor

// 0x008a2440 - Constructor for an unknown class (likely derived from base at 0x004bedc0)
// Sets vtable pointer at offset 0 and a secondary pointer at offset 4 (possibly RTTI or second vtable)
void* __fastcall UnknownClass::constructor(void* this)
{
    // Call base class constructor
    FUN_004bedc0(this);

    // Set the vtable pointer (primary)
    *(void**)this = &PTR_FUN_00d79048;

    // Set secondary pointer at offset +0x4 (could be RTTI descriptor or second vtable for multiple inheritance)
    *(void**)((char*)this + 4) = &PTR_LAB_00d79040;

    return this;
}