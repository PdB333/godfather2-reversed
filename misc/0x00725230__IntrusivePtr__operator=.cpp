// FUNC_NAME: IntrusivePtr::operator=
// Address: 0x00725230
// Role: Copy assignment operator for a custom intrusive smart pointer.
// The class layout (offsets):
// +0x00: value data (e.g., handle index or identifier)
// +0x04: pointer to managed object (T*)
// +0x08: previous back-pointer (used to store the previous value of managed->backlink)
// The managed object T has at +0x04 a backlink pointer that points to the smart pointer's +0x04 field.
// This allows the managed object to nullify the pointer when it is destroyed.

IntrusivePtr* __thiscall IntrusivePtr::operator=(IntrusivePtr* this, IntrusivePtr* other)
{
    int* oldPtr;
    int* newPtr;

    // Copy the first field (typically a handle value or reference count modifier)
    this[0] = *other;

    // Self-assignment check: if the address of the pointer fields are identical, skip
    if (&this[1] == &other[1]) {
        return this;
    }

    newPtr = other[1];               // get new managed pointer (int*)
    oldPtr = this[1];                // get current managed pointer

    if (oldPtr != newPtr) {
        // Release the old pointer if it exists
        if (oldPtr != 0) {
            FUN_004daf90(&this[1]);  // release or decrement reference
        }

        this[1] = newPtr;           // assign new pointer

        if (newPtr != 0) {
            // Store the old backlink from the managed object into our +0x08 field
            this[2] = *(int**)(newPtr + 1);   // save old back-pointer (offset +0x04 in T)
            // Update the managed object's backlink to point to our pointer field (+0x04 in this)
            *(int**)(newPtr + 1) = &this[1];
        }
    }

    return this;
}