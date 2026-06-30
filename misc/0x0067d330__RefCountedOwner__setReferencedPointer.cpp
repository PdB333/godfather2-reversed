// FUNC_NAME: RefCountedOwner::setReferencedPointer
void __thiscall RefCountedOwner::setReferencedPointer(void* newObject) {
    // Release old object at offset +0x18 (m_object)
    void* oldObject = *(void**)(this + 0x18);
    if (oldObject != nullptr) {
        // Virtual function at vtable offset 0xC (Release)
        void (**vtable)(void) = *(void (***)(void))oldObject;
        vtable[3](); // +0xC = 3rd function (0-indexed after this pointer)
    }

    // Store new pointer
    *(void**)(this + 0x18) = newObject;

    // AddRef new object if non-null
    if (newObject != nullptr) {
        // Virtual function at vtable offset 0x8 (AddRef)
        void (**vtable)(void) = *(void (***)(void))newObject;
        vtable[2](); // +0x8 = 2nd function
    }
}