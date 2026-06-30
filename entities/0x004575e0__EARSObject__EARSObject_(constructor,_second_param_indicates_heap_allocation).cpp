// FUNC_NAME: EARSObject::EARSObject (constructor, second param indicates heap allocation)
EARSObject* __thiscall EARSObject::EARSObject(EARSObject* this, byte heapAllocated) {
    // +0x00 : this
    // Call base class constructor at 0x00457600 (likely SimObject::SimObject)
    BaseClass::BaseClass(this);
    // If the object was allocated on the heap (heapAllocated & 1), deallocate it.
    // This pattern is typical of EA engine constructors: the allocator passes
    // a flag to indicate whether the object should be freed if construction fails.
    if (heapAllocated & 1) {
        operator delete(this);  // 0x009c8eb0 - free memory
    }
    return this;
}