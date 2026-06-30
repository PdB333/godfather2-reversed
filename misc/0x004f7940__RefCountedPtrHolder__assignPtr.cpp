// FUNC_NAME: RefCountedPtrHolder::assignPtr
void RefCountedPtrHolder::assignPtr(int* newPtr) {
    // Release the previous pointer if it exists
    if (this->m_ptr != nullptr) {
        // Decrement reference count at offset +0x04 of the pointed object
        int* refCount = reinterpret_cast<int*>(this->m_ptr + 4);
        (*refCount)--;

        // If reference count reached zero, call the Release virtual method (vtable entry at offset +0x04)
        if (reinterpret_cast<int*>(this->m_ptr)[1] == 0) {
            (*(void (**)(void))(*(int*)this->m_ptr + 4))();
        }

        this->m_ptr = nullptr;
    }

    // Assign the new pointer
    this->m_ptr = newPtr;

    // Increment reference count of the new pointer if it's non-null
    if (newPtr != nullptr) {
        int* refCount = reinterpret_cast<int*>(newPtr + 4);
        (*refCount)++;
    }
}