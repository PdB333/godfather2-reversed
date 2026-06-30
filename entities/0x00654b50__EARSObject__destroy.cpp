// FUNC_NAME: EARSObject::destroy
// Address: 0x00654b50
// Destroys an EARSObject by decrementing reference counts on three child objects,
// calling base destructor, and optionally freeing memory.
int __thiscall EARSObject::destroy(void* this, byte freeMemory) {
    // Release child object at +0x20 (third child)
    int* pChild1 = *(int**)((char*)this + 0x20);
    if (pChild1 != nullptr) {
        int* refCount = pChild1 + 2; // reference count at offset 8
        *refCount -= 1;
        if (*refCount == 0) {
            // Virtual destructor at vtable index 2 (offset 8)
            void (**vtable)(void) = *(void (***)(void))pChild1;
            vtable[2]();
        }
    }

    // Release child object at +0x1c (second child)
    int* pChild2 = *(int**)((char*)this + 0x1c);
    if (pChild2 != nullptr) {
        int* refCount = pChild2 + 2;
        *refCount -= 1;
        if (*refCount == 0) {
            void (**vtable)(void) = *(void (***)(void))pChild2;
            vtable[2]();
        }
    }

    // Release child object at +0x18 (first child)
    int* pChild3 = *(int**)((char*)this + 0x18);
    if (pChild3 != nullptr) {
        int* refCount = pChild3 + 2;
        *refCount -= 1;
        if (*refCount == 0) {
            void (**vtable)(void) = *(void (***)(void))pChild3;
            vtable[2]();
        }
    }

    // Call base class destructor (likely EARSBase::~EARSBase)
    EARSBase::onDestroy(); // Placeholder for FUN_0064b440

    // Optionally free memory (freeMemory & 1)
    if (freeMemory & 1) {
        operator delete(this); // Placeholder for FUN_009c8eb0
    }

    return this;
}