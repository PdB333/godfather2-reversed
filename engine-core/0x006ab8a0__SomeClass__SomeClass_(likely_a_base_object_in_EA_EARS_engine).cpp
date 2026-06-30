// FUNC_NAME: SomeClass::SomeClass (likely a base object in EA EARS engine)
// Address: 0x006ab8a0
// Role: Constructor initializing vtable, embedded subobjects, and calling base & cleanup functions

void __thiscall SomeClass::constructor(SomeClass *this) {
    // Set primary vtable pointer for this class
    this->vtable = (void *)&PTR_FUN_00d5da30; // +0x00

    // Additional vtable-like entries at fixed offsets
    this->field_0x3C = (void *)&PTR_LAB_00d5da20; // +0x3C
    this->field_0x48 = (void *)&PTR_LAB_00d5da1c; // +0x48

    // Initialize three embedded sub-objects with a known construction pattern
    // Each pair of calls (0x408310, 0x4086d0) initializes two separate fields within the sub-object?
    initSubObjectA((uint8_t *)this + 0x60); // +0x60 (index 0x18)
    setupSubObjectB((uint8_t *)this + 0x50); // +0x50 (index 0x14)
    initSubObjectA((uint8_t *)this + 0x50);  // again at +0x50
    setupSubObjectB((uint8_t *)this + 0x58); // +0x58 (index 0x16)
    initSubObjectA((uint8_t *)this + 0x58);  // again at +0x58

    // Call base class constructor (likely sets up core object state)
    baseClassConstructor(this);

    // If a pointer at +0x88 is non-null, call a member function pointer at +0x94 on it
    if (this->field_0x88 != 0) {
        void (*func)(void *) = *(void (**)(void *))((uint8_t *)this + 0x94);
        func(this->field_0x88);
    }

    // Global post-construction hook (e.g., registration, reference counting)
    postConstructionCleanup();
}