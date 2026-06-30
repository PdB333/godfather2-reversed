// FUNC_NAME: Entity::constructor

// Constructor for an entity-like object. 
// param_2 (allocationFlag) bit 0 indicates if memory was dynamically allocated.
// If set, a deallocation function is called (likely to handle custom memory management).
// Base class initialization is performed first.

void __thiscall Entity::constructor(byte allocationFlag) {
    // Call base class constructor (likely passes this implicitly)
    BaseClass::constructor(this); // FUN_004e4f40 - assumed base constructor

    // If the object was heap-allocated (bit 0 set), perform additional cleanup registration
    if (allocationFlag & 1) {
        this->deallocateMemory(); // FUN_009c8eb0 - deallocation/cleanup hook
    }
}