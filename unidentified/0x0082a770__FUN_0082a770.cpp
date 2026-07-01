// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(SomeClass* this) {
    // Set primary vtable pointer at offset 0x0
    this->vtable1 = &PTR_FUN_00d737b4;
    // Call base class constructor (likely initializes base members)
    FUN_0082a730();
    // Set secondary vtable pointer at offset 0x30
    this->vtable2 = &PTR_FUN_00d7343c;
    // Check if sub-object pointer at offset 0x8C is non-null
    if (this->subObjectPtr != nullptr) {
        // Destroy the sub-object (e.g., a dynamically allocated component)
        FUN_004daf90(&this->subObjectPtr);
    }
    // Override secondary vtable with a different one (possibly for derived behavior)
    this->vtable2 = &PTR_LAB_00e32854;
    // Call additional initialization routine
    FUN_00821f60();
}