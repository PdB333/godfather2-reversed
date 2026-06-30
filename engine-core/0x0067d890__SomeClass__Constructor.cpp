// FUNC_NAME: SomeClass::Constructor
// Address: 0x0067d890
// Role: Constructor for a class with vtable at 0x00d57fa8.
// The second parameter indicates whether the object is heap-allocated;
// if bit 0 is set, the deallocation function is called on failure or destruction.

undefined4* __thiscall SomeClass::Constructor(undefined4* this, byte heapAllocatedFlag)
{
    // Set vtable pointer to the class's vtable table
    *this = &PTR_FUN_00d57fa8;

    // Call base class initialization (likely sets up common members)
    FUN_004149b0();

    // If the object was dynamically allocated, call the deallocation routine
    // (this is often used in placement new with a flag indicating heap allocation)
    if ((heapAllocatedFlag & 1) != 0) {
        FUN_009c8eb0(this);  // deallocation (e.g., operator delete)
    }

    return this;
}