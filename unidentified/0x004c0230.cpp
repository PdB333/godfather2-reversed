// FUN_004c0230: EARSObject::EARSObject
EARSObject::EARSObject(bool heapAllocated) {
    // Base initialization (likely virtual table setup, member zeroing)
    this->initObject();
    // If the object was allocated on the heap (flag bit 0 set),
    // perform additional heap-specific initialization (e.g., register in heap manager)
    if (heapAllocated) {
        this->onHeapAllocated();
    }
    // Note: Constructor does not return a value in C++; the 'this' pointer is implicit.
}