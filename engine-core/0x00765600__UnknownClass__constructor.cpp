// FUNC_NAME: UnknownClass::constructor

// Constructor for class with vtable at 0x00d63090 (likely EA EARS engine object)
// Address: 0x00765600
// param_2: bit 0 controls whether to call cleanup/destructor (e.g., for placement new)
void * __thiscall UnknownClass::constructor(void *this, byte flags) {
    // Set vtable pointer
    *(void **)this = &PTR_LAB_00d63090; // vtable for class

    // If the member at offset +0x68 (this[0x1a]) is non-null, release it
    if (*(int *)((char *)this + 0x68) != 0) {
        subObjectDestructor((void *)((char *)this + 0x68));
    }

    // Global initialization call (e.g., register instance, initialize subsystem)
    globalInitFunction();

    // If flags bit 0 is set, call cleanup/destructor on this (e.g., operator delete)
    if ((flags & 1) != 0) {
        deleteOrCleanup(this);
    }

    return this;
}