// FUNC_NAME: SomeClass::SomeClass
void* __thiscall SomeClass::SomeClass(void* this, byte allocFlag) {
    // Call base constructor
    BaseClass::BaseClass(this);
    // If dynamically allocated (bit 0 set), perform additional allocation setup
    if (allocFlag & 1) {
        // Call custom allocator callback with object size 0x20c (524 bytes)
        ::setupAllocatedObject(this, 0x20c);
    }
    return this;
}