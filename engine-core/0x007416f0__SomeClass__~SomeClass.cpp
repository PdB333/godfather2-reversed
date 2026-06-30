// FUNC_NAME: SomeClass::~SomeClass
SomeClass * __thiscall SomeClass::~SomeClass(SomeClass *this, byte destroyFlags)
{
    // Set vtable to static destructor vtable (likely prevents double deletion)
    *(int *)this = &PTR_LAB_00d63ab0;

    // Destroy member at offset +0x50 (0x14 * 4) if non-null
    if (this->subObjectPtr != 0) {
        FUN_004daf90(this + 0x14); // Likely sub-object destructor
    }

    // Global/engine-level cleanup
    FUN_004ac1e0();

    // If destroyFlags bit 0 is set, deallocate memory
    if ((destroyFlags & 1) != 0) {
        FUN_00624da0(this); // operator delete
    }

    return this;
}