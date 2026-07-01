// FUNC_NAME: BaseObject::BaseObject
// Address: 0x0082bfd0
// Constructor for BaseObject (likely a base class in the EARS engine hierarchy).
// Calls a base init function at 0x0082b490.
// If the allocationFlag (bit 0 of param_2) is set, calls an additional init at 0x009c8eb0
// (possibly for heap-allocated objects or deferred setup).

BaseObject::BaseObject(byte allocationFlag) {
    // Call base class initialization (FUN_0082b490)
    initBase();

    if (allocationFlag & 1) {
        // Additional initialization (FUN_009c8eb0)
        initHeap();
    }
}