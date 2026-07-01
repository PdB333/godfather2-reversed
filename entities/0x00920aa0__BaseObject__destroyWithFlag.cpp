// FUNC_NAME: BaseObject::destroyWithFlag
// Address: 0x00920aa0
// Role: Custom destruction wrapper that optionally deallocates memory.
// This is a common pattern in EA EARS engine for objects that need
// cleanup followed by conditional heap deallocation (flag bit 0).
int* BaseObject::destroyWithFlag(byte flag) {
    if (this != 0) {
        // Call internal cleanup/desctructor logic
        cleanupInternal();
    }
    if (flag & 1) {
        // Deallocate memory via heap manager
        heapFree(this);
    }
    return this;
}