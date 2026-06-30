// FUNC_NAME: SomeClass::Destroy (Destructor/Cleanup)
// Function address: 0x00671ab0
// Role: Cleans up two referenced objects, decrements reference counts, frees memory

void __thiscall SomeClass::Destroy(void) {
    int *ptr;
    int objA;    // Pointer to first managed object (from this+6)
    int objB;    // Pointer to second managed object (from this+2)
    int manager; // Pointer to a manager structure (from this+0xf1c)

    // Pre-destruction steps: likely zeroing flags or calling base destructors
    FUN_00672320(); // Sub-destructor
    *(int *)this = 0; // Zero the first 4 bytes? (in_EAX, but actually sets *this to 0)
    FUN_00671c20(); // Another sub-destructor

    // Process first managed object (stored at this+6)
    objA = *(int *)((char *)this + 6);
    manager = *(int *)((char *)this + 0xf1c); // Manager pointer
    if (objA != 0) {
        // Remove reference from manager's array: manager->array[objA->index] = 0
        // objA points to an object with an index at offset -8
        *(int *)(*(int *)(manager + 0xc) + *(int *)(objA - 8) * 4) = 0;
        // Decrement manager's reference count
        ptr = (int *)(manager + 4);
        *ptr = *ptr - 1;
        // Free the object memory (object header size 0x10)
        (*(void (__stdcall *)(void *))DAT_01206694)((void *)(objA - 0x10));
    }

    // Process second managed object (stored at this+2)
    objB = *(int *)((char *)this + 2);
    manager = *(int *)((char *)this + 0xf1c); // Re-fetch manager (could be same)
    // Zero a short at this+4 (likely a flag)
    *(short *)((char *)this + 4) = 0;
    if (objB != 0) {
        // Same pattern: remove reference and free object
        *(int *)(*(int *)(manager + 0xc) + *(int *)(objB - 8) * 4) = 0;
        ptr = (int *)(manager + 4);
        *ptr = *ptr - 1;
        (*(void (__stdcall *)(void *))DAT_01206694)((void *)(objB - 0x10));
    }

    // Re-fetch manager after modifications (could be same object)
    manager = *(int *)((char *)this + 0xf1c);
    // Zero the first short (this+0)
    *(short *)this = 0;

    // Post-destruction cleanup
    FUN_00672fd0();

    // Free the manager's internal array
    (*(void (__stdcall *)(void *))DAT_01206694)(*(void **)(manager + 0xc));
    // Free the manager structure itself
    (*(void (__stdcall *)(void *))DAT_01206694)((void *)manager);
    // Additional free (possibly the this pointer? but no argument shown)
    // The decompiled shows a call with no argument; likely a mistake in Ghidra.
    // Possibly frees something else, but omitted for now.
}