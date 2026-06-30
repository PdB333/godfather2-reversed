// FUNC_NAME: SomeClass::initFromSource
// Address: 0x004f8e60
// Role: Initializes an object from a source template, copying fields and setting up TLS-based storage.

void __thiscall SomeClass::initFromSource(void* source) {
    // Call some initialization helper
    FUN_00533cc0();

    // Set vtable pointer
    *(void**)this = &PTR_FUN_00e379c8;

    // Check flag at source+0x0d
    if (*(char*)((int)source + 0x0d) == '\0') {
        // Copy source pointer to this+0x24
        *(void**)((int)this + 0x24) = source;

        // Copy field from source+0x24 to this+0x2c
        *(int*)((int)this + 0x2c) = *(int*)((int)source + 0x24);

        // Conditional copy based on float at source+0x20
        if (*(float*)((int)source + 0x20) == 0.0f) {
            *(int*)((int)this + 0x28) = *(int*)((int)source + 0x1c);
        } else {
            *(int*)((int)this + 0x28) = 0;
        }

        // Access thread-local storage via FS segment
        int* tlsArray = *(int**)__readfsdword(0x2c); // FS:0x2c -> TLS array pointer
        int index = *(int*)((int)this + 0x10); // this+0x10

        // Clear fields at this+0x34 and this+0x30
        *(int*)((int)this + 0x34) = 0;
        *(int*)((int)this + 0x30) = 0;

        // Get a buffer from TLS array +8
        int* buffer = (int*)*(tlsArray + 2); // offset 8 = 2 ints

        // Copy three ints from source+4,8,0xc to buffer+0x40+index
        buffer[0x10 + index] = *(int*)((int)source + 4);      // offset 0x40/4 = 0x10
        buffer[0x11 + index] = *(int*)((int)source + 8);
        buffer[0x12 + index] = *(int*)((int)source + 0x0c);
    }
}