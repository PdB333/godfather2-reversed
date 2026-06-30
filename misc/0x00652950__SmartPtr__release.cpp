// FUNC_NAME: SmartPtr::release
void __thiscall SmartPtr::release(void) {
    // Release the ref-counted object pointed to by the internal pointer.
    // The object has a reference count at offset +0x08 and a vtable at +0x00.
    // The third virtual function (offset 8 in vtable) is the destructor/onLastRef.
    RefCounted* obj = this->m_object;
    if (obj != nullptr) {
        int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(obj) + 8);
        (*refCount)--;
        if (*refCount == 0) {
            // Call virtual destructor via vtable
            void (*destroy)(RefCounted*) = reinterpret_cast<void (*)(RefCounted*)>(*(int*)obj + 8);
            destroy(obj);
        }
    }
}