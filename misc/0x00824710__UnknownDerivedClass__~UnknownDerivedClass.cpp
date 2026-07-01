// FUNC_NAME: UnknownDerivedClass::~UnknownDerivedClass
// Address: 0x00824710
// Role: Destructor for a class derived from another class. Sets vtable to derived, cleans up a pointer member at offset 0x5C (0x17*4), then sets vtable to base.
void __thiscall UnknownDerivedClass::~UnknownDerivedClass(void)
{
    // Set vtable to derived class vtable (most derived type)
    *(void**)this = &PTR_FUN_00d7343c;

    // Check if pointer at offset +0x5C is non-null
    void* memberPtr = *(void**)((char*)this + 0x5C);
    if (memberPtr != nullptr) {
        // Destroy the pointed object (likely a subobject or component)
        FUN_004daf90(memberPtr);
    }

    // Set vtable to base class vtable (base type)
    *(void**)this = &PTR_LAB_00e32854;

    // Note: Base destructor is not called here; may be called by the compiler after this function returns
}