// FUNC_NAME: RefCountedObject::release
// Address: 0x00652950
// Purpose: Decrements reference count and deletes object if it reaches zero.
// Typical EA EARS engine pattern: vtable[0] = some virtual, vtable[1] = AddRef, vtable[2] = Release? 
// The code treats the value at vtable+8 as a counter, then calls the function at vtable+8 if counter hits 0.
// This suggests vtable[2] is used as both a reference count and a function pointer (unusual but possible in some custom allocators).
void RefCountedObject::release() {
    // Get the vtable pointer or internal structure pointer from the object's first field.
    int* vtable = *(int**)this;  // *this → pointer to some memory (possibly a vtable or an atom)
    if (vtable != nullptr) {
        // Offset +0x08 from that pointer is treated as a reference count.
        int* refCountPtr = vtable + 2;  // vtable[2] at offset 8
        int refCount = *refCountPtr;
        refCount--;
        *refCountPtr = refCount;
        if (refCount == 0) {
            // Call the destructor (or deallocator) via the same vtable[2] — interpreted as a function pointer.
            // This is a self-destruction call: (*(void (*)())(vtable[2]))(this);
            void (*destructor)(void) = (void (*)())(*(int*)vtable + 8);
            destructor();
        }
    }
}