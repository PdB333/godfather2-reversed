// FUNC_NAME: assignRefCountedPtr
// Address: 0x0065e830
// Role: Replaces a reference-counted pointer with a new one, releasing the old and retaining the new.
// Assumes objects have a vtable at offset 0, reference count at offset +0x8,
// and a virtual destructor at vtable offset +0x8 (index 2).

void assignRefCountedPtr(int *&dest, int *src)
{
    // Release old pointer
    int *oldObj = dest;
    if (oldObj != nullptr)
    {
        int *refCount = oldObj + 2; // +0x8 (offset of reference count in bytes)
        (*refCount)--;
        if (*refCount == 0)
        {
            // Call virtual destructor via vtable (third entry at offset +0x8)
            void (*destructor)(void *) = *(void (**)(void *))(*(int *)oldObj + 8);
            destructor(oldObj);
        }
    }

    // Assign new pointer
    dest = src;

    // Retain new pointer
    if (src != nullptr)
    {
        int *refCount = src + 2; // +0x8
        (*refCount)++;
    }
}