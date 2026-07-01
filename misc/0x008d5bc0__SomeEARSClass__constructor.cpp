// FUNC_NAME: SomeEARSClass::constructor
// Constructs an object with a base class initializer and optional deallocation if heap-allocated flag is set
uint __thiscall SomeEARSClass::constructor(uint this, byte flags) {
    // Call base class constructor
    EARSBaseClass::constructor(this); // FUN_008d4b80

    // If the heap-allocated flag (bit 0) is set, deallocate this instance
    if ((flags & 1) != 0) {
        MemoryManager::deallocate(this, 0x9c); // FUN_0043b960 - deallocate with size 0x9c
    }

    return this;
}