// FUNC_NAME: SomeClass::~SomeClass

// Destructor for SomeClass (derived from BaseClass).
// Calls base destructor and deallocates memory if this object was heap-allocated.
// param_1 (this): pointer to the object
// param_2: flags (bit 0 = 1 indicates dynamic allocation, triggers deallocation)
void __thiscall SomeClass::~SomeClass(void *this, byte flags) {
    // Call base class destructor (BaseClass::~BaseClass)
    BaseClass::~BaseClass();

    // If the object was allocated on the heap, release its memory
    if ((flags & 1) != 0) {
        operatorDelete(this); // Custom deallocation function
    }
}