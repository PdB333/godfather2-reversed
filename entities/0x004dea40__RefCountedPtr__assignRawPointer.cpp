// FUNC_NAME: RefCountedPtr::assignRawPointer
// Address: 0x004dea40
// Role: Smart pointer assignment with reference counting.
// Decrements ref count of current pointed object, deletes if zero,
// then assigns new pointer and increments its ref count.
// Returns a pointer to the smart pointer (this).

int* __thiscall RefCountedPtr::assignRawPointer(int* thisPtr, int newPtr)
{
    int* currentPtr;
    int* refCountPtr;

    // If currently pointing to an object, decrease its reference count
    if (*thisPtr != 0) {
        currentPtr = (int*)*thisPtr;                  // current object pointer
        refCountPtr = (int*)((int)currentPtr + 4);    // ref count at +0x04
        *refCountPtr = *refCountPtr - 1;              // decrement

        // If reference count is now zero, delete the object
        if (*(int*)((int)currentPtr + 4) == 0) {
            // Call destructor via vtable at offset +0x04 (likely
            // a virtual destructor or release function)
            (**(code**)(*(int*)currentPtr + 4))();
        }

        // Clear pointer before assigning new one (safety)
        *thisPtr = 0;
    }

    // Assign new raw pointer
    *thisPtr = newPtr;

    // If new pointer is not null, increment its reference count
    if (newPtr != 0) {
        *(int*)(newPtr + 4) = *(int*)(newPtr + 4) + 1;  // ref count at +0x04
    }

    // Return pointer to smart pointer (this)
    return thisPtr;
}