// FUNC_NAME: SomeClass::SomeClass
SomeClass * __thiscall SomeClass::SomeClass(uint8_t allocFlag)
{
    // Set vtable pointer to base class vtable (at offset 0)
    this->vtable = &BaseClassVTable1;
    // Call base class constructor (using placement new style)
    baseClassConstructor(0);
    // Override vtable pointer to derived class vtable
    this->vtable = &DerivedClassVTable;
    // Perform additional initialization (likely another base or component init)
    derivedInit();
    // If allocFlag indicates heap allocation, call destructor/deallocator
    if ((allocFlag & 1) != 0) {
        destructorOrDealloc(this);
    }
    return this;
}