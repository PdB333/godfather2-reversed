// FUNC_NAME: EARSHeapObject::construct

// @ 0x007f2ef0 - Placement constructor with memory management flag
// flag: bit 0 set means free memory (call destructor), clear means fresh allocation
uint32_t __thiscall EARSHeapObject::construct(uint32_t thisPtr, byte flag)
{
    // Call the actual initialization logic (likely base class constructor or init)
    this->initialize(); // FUN_007f2d40

    // If memory should be freed, call the destructor/deallocator
    if ((flag & 1) != 0) {
        EARSHeapObject::deallocate(thisPtr); // FUN_009c8eb0
    }

    return thisPtr;
}