// FUNC_NAME: SomeClass::~SomeClass()
// Function at 0x0073d650: Destructor for SomeClass - performs two-stage object cleanup with vtable switching, sub-object destruction, global cleanup, and conditional deallocation.

SomeClass::~SomeClass(byte deleteFlag)
{
    // Set vtable to derived class vtable
    this->vtable = &Vtable1;

    // Destroy sub-object at offset 0x1c (likely a container or string)
    if (this->subObject1 != 0) {
        destroySubObject(&this->subObject1);
    }

    // Switch to base class vtable (for second inheritance branch)
    this->vtable = &Vtable2;

    // Destroy sub-object at offset 0x1a (another member)
    if (this->subObject2 != 0) {
        destroySubObject(&this->subObject2);
    }

    // Global cleanup call (e.g., EARS engine shutdown step)
    someGlobalCleanup();

    // If delete flag is set, deallocate this object
    if ((deleteFlag & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}