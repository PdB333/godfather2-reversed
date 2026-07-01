// FUNC_NAME: LinkableObject::Destroy
// Address: 0x008db8a0
// Role: Destructor that unlinks this object from a doubly-linked list and optionally deallocates memory.
// The object has a vtable at offset +0x28, and list pointers at offsets +0x18 (prev), +0x1c (next), +0x20 (data).

int __thiscall LinkableObject::Destroy(void* thisPtr, byte flags)
{
    // Set vtable to a specific destroyed vtable (likely to prevent further virtual calls)
    *(void***)((int)thisPtr + 0x28) = &PTR_LAB_00e317cc;

    // Unlink from linked list: the object itself is a node with prev, next, and a data pointer.
    // The data pointer at +0x20 is used to repoint the neighbor's link fields.
    int prev = *(int*)((int)thisPtr + 0x18);
    int next = *(int*)((int)thisPtr + 0x1c);
    int data = *(int*)((int)thisPtr + 0x20);

    if (prev != 0) {
        if (next == 0) {
            // No next: update prev's forward link to point to this node's data
            *(int*)(prev + 4) = data;
        } else {
            // Has next: update next's back link to point to this node's data
            *(int*)(next + 8) = data;
        }
        if (data != 0) {
            // Update the data object's back link to point to the previous node
            *(int*)(data + 4) = next;
        }
    }

    // Call base destruction/cleanup routine
    FUN_0064d150();

    // If bit 0 of flags is set, free the memory
    if ((flags & 1) != 0) {
        FUN_009c8eb0(thisPtr); // operator delete (probably)
    }

    return (int)thisPtr;
}