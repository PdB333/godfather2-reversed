// FUNC_NAME: RefCounted::release

// Function at 0x00652910
// EA EARS reference count decrement and conditional deletion.
// This is a typical __thiscall member function: the 'this' pointer is passed in ECX (EAX in the decompiled view).
// The object's first field is a pointer to a reference count control block.
// The control block layout: [vtable pointer (4 bytes)][refcount (4 bytes)]? Actually we access offset 8.
// So control block: +0x00: vtable pointer, +0x04: ?, +0x08: refcount.
void __thiscall RefCounted::release(void)
{
    // Read the pointer to the refcount control block from the object's first field
    int *refCountBlock = *(int **)this;
    
    if (refCountBlock != (int *)0x0) {
        // Point to the reference count at offset 8 of the control block (i.e. refCountBlock + 2 ints)
        int *refCount = refCountBlock + 2;
        *refCount = *refCount - 1;
        
        if (*refCount == 0) {
            // Call the virtual destructor located at vtable offset 8 of the control block.
            // This destroys the object (and possibly the control block).
            (*(void (__thiscall **)(void *))(*refCountBlock + 8))(this);
        }
    }
    return;
}