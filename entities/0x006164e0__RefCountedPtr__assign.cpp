// FUNC_NAME: RefCountedPtr::assign
// Function address: 0x006164e0
// Role: Assigns a new pointer to a reference-counted pointer, releasing the old one and acquiring the new one.
// The managed object has a 16-bit reference count at offset +8.
// Global vtable at DAT_01205964 is used for deletion (calls second virtual function: operator delete?).

void __thiscall RefCountedPtr::assign(int* newPtr)
{
    int* oldPtr = this->m_ptr; // +0x00: stored pointer

    // If old and new pointers are the same, do nothing.
    if (oldPtr != newPtr) {
        // Release old pointer if it exists.
        if (oldPtr != 0) {
            // Decrement reference count at offset +8.
            short* refCount = (short*)(oldPtr + 8);
            *refCount = *refCount - 1;
            // If count reaches zero, destroy the object and free memory.
            if (*refCount == 0) {
                // Call the destructor (virtual?) – FUN_00616dc0
                destructObject(oldPtr);
                // Call virtual function from global vtable to delete memory.
                // The vtable is at *DAT_01205964, second entry (offset +4) takes object and 0.
                callDelete(oldPtr);
            }
            this->m_ptr = 0;
        }
        // Acquire new pointer if it exists.
        if (newPtr != 0) {
            // Increment reference count at offset +8.
            short* refCount = (short*)(newPtr + 8);
            *refCount = *refCount + 1;
            this->m_ptr = newPtr;
        }
    }
}