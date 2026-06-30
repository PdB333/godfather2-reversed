// FUNC_NAME: SomeDerivedClass::~SomeDerivedClass
SomeDerivedClass * __thiscall ~SomeDerivedClass(SomeDerivedClass *this, byte deleteFlag) {
    // Set vtable pointer to most derived class (0x00d5fc10)
    this->vtable = &SomeDerivedClass_vtable; // +0x00: vtable pointer
    // Call base class destructor to clean up base portion
    SomeBaseClass::~SomeBaseClass(this);
    // If the object was allocated on the heap (flag bit 0 set), free memory
    if (deleteFlag & 1) {
        operator delete(this);
    }
    return this;
}