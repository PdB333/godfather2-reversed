// FUNC_NAME: SomeClass::allocationAwareConstructor
undefined4 __thiscall SomeClass::allocationAwareConstructor(byte shouldFreeOnError) {
    // Call the base class constructor (likely the actual initialization)
    // Address: 0x005f6630
    this->baseConstructor();

    // If the 'shouldFreeOnError' flag has bit 0 set,
    // deallocate the object immediately.
    // This is a defensive pattern: if the caller indicates the memory
    // should be freed on failure (e.g., heap allocation vs placement),
    // we free it after construction. In practice, this might be used
    // when the constructor allocation policy is variant, or as part of
    // a custom new/delete override.
    if ((shouldFreeOnError & 1) != 0) {
        // operator delete or custom deallocator at 0x009c8eb0
        this->operator delete(this);
    }

    // Return the constructed (or freed) pointer
    return this;
}