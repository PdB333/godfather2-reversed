//FUNC_NAME: SomeClass::SomeClass
// Function address: 0x008cc760 - Constructor for SomeClass
// Calls base class constructor at 0x00414970 and sets vtable pointer

SomeClass::SomeClass(int param2, int param3) {
    // Call base class constructor (likely EARS object or game entity)
    BaseClassConstructor(param2, param3);
    // Set vtable pointer to class-specific vtable
    this->vtable = &SomeClass_vtable;
}