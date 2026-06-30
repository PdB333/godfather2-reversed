// FUNC_NAME: SomeDerivedClass::SomeDerivedClass
// 0x00469ba0: Constructor for a derived class. Sets base vtable, calls base default constructor,
// then sets derived vtable. The byte parameter likely indicates heap allocation (bit 0 set = allocated),
// triggering additional per-heap initialization via FUN_009c8eb0.
// Vtables: Base -> PTR_FUN_00e322ec, Derived -> PTR_LAB_00e30ea0

void* SomeDerivedClass::SomeDerivedClass(byte allocFlag) {
    // Set vtable to base class
    this->vtable = &BaseClass_vtable;

    // Call base class default constructor
    FUN_0043e380(this);

    // Set vtable to this derived class
    this->vtable = &SomeDerivedClass_vtable;

    // If the object was heap-allocated (allocFlag & 1), perform additional setup
    // (likely allocating or initializing heap-specific data)
    if (allocFlag & 1) {
        FUN_009c8eb0(this);
    }

    return this;
}