// FUNC_NAME: allocateSmallObjectWithInitialization

// Reconstructed from 0x005f9cc0. This __thiscall member function allocates a 12-byte block
// via a virtual allocator (vtable[0]) and initializes three 4-byte fields.
// The internal buffer pointer at offset +0x04 (this+4) is used as a fallback if not null.
// unaff_retaddr likely corresponds to a register value (e.g., EDX) from the calling context.
void __thiscall allocateSmallObjectWithInitialization(void* thisPtr, void* srcPtr)
{
    // Internal pool/buffer at this+4 (possibly preallocated space or null)
    void* internalBuffer = *(void**)((char*)thisPtr + 4);
    int fallback[3]; // local_c, local_8, local_4 (stack fallback)
    int unknownReg;  // unaff_retaddr – value from a register, not reliably captured in C++
    void* buffer;

    if (internalBuffer == nullptr) {
        // Fallback: use stack buffer, all zeros
        fallback[0] = 0;
        fallback[1] = 0;
        fallback[2] = 0;
        buffer = fallback;
    } else {
        buffer = internalBuffer;
    }

    // Virtual allocator: vtable[0](size=0xc, buffer) returns a pointer
    void* (*allocator)(int, void*) = *(void* (*)(int, void*))(*(void**)thisPtr);
    void* allocated = allocator(12, buffer);

    // Write three fields into the allocated block
    if (allocated) {
        *(int*)allocated = fallback[2]; // First field: local_4 (0 in fallback, else undefined)
    }
    if ((int*)allocated + 1) {
        *((int*)allocated + 1) = unknownReg; // Second field: from register (unaff_retaddr)
    }
    if ((int*)allocated + 2) {
        *((int*)allocated + 2) = *(int*)srcPtr; // Third field: first int from source
    }
}