// FUNC_NAME: SomeBaseClass::attachPointer
// Function at 0x005fa2e0 - Assigns a pointer to an object with vtable callbacks (likely for reference counting or ownership).
// Uses an external helper at 0x004265d0 (acquireHandle) and virtual functions at vtable offsets 4, 8, 12.

void SomeBaseClass::attachPointer(void* obj) {
    // Temporary buffer (held in register EDI in original) to store two pointers: this and a handle.
    void* tempPair[2];
    void** buf = tempPair;

    *buf = this; // Store 'this' as the first element.

    // Call virtual method at vtable offset 8 (e.g., onAttachPrepare)
    (**(code **)(*(int*)this + 8))();

    if (obj != 0) {
        // Acquire a handle/reference for obj using this as owner.
        void* handle = acquireHandle(obj, this); // 0x004265d0
        buf[1] = handle;

        // Call virtual method at vtable offset 4 (e.g., onAttachAssign) with obj and flag 0.
        (**(code **)(*(int*)this + 4))(obj, 0);

        // Call virtual method at vtable offset 12 (e.g., onAttachFinalize)
        (**(code **)(*(int*)this + 12))();
    } else {
        buf[1] = 0;

        // Call virtual method at vtable offset 12 (e.g., onAttachFinalize)
        (**(code **)(*(int*)this + 12))();
    }
}