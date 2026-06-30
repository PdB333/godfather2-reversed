// FUNC_NAME: RefCountedPtr::operator=
void RefCountedPtr::operator=(const RefCountedPtr& other) {
    // this is in ECX, but decompiler used EDI (unaff_EDI). Assume this->mPtr is at offset 0.
    RefCounted* oldPtr = this->mPtr;
    RefCounted* newPtr = other.mPtr;

    // Decrement old reference count if non-null
    if (oldPtr) {
        // Reference count is at offset 8 (2 ints from base), stored as int
        int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(oldPtr) + 8);
        *refCount -= 1;
        if (*refCount == 0) {
            // Call virtual Release/destructor (vtable[2] = offset 8)
            void (*releaseFunc)(RefCounted*) = reinterpret_cast<void (*)(RefCounted*)>(
                (*reinterpret_cast<int**>(oldPtr))[2]);
            releaseFunc(oldPtr);
        }
    }

    // Assign new pointer
    this->mPtr = newPtr;

    // Increment new reference count if non-null
    if (newPtr) {
        int* refCount = reinterpret_cast<int*>(reinterpret_cast<char*>(newPtr) + 8);
        *refCount += 1;
    }
}