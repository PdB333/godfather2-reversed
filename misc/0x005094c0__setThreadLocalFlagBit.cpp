// FUNC_NAME: setThreadLocalFlagBit
// Function at 0x005094c0: Sets a bit in a per-thread data structure accessed via TLS.
// Uses FS segment (Thread Environment Block) to retrieve TLS array slot 2.
// That slot holds a pointer to a base integer. The actual byte to modify is at
// base + slotIndex * 0x50 + 0x54 + *offsetPtr.
// The slot index is passed in the EAX register.
void __cdecl setThreadLocalFlagBit(int *offsetPtr, unsigned char bitMask)
{
    // GCC/Clang doesn't support __readfsdword directly; below assumes MSVC intrinsics.
    // For portability, you'd need inline assembly: __asm { mov eax, fs:[0x2c] }
    void *tlsArray = (void *)__readfsdword(0x2C);  // TEB + 0x2C → TLS array pointer
    if (tlsArray == NULL) return;

    // TLS slot index 2 (at offset 8 bytes) contains a pointer to a pointer to a base integer
    int *basePtr = *(int **)((unsigned char *)tlsArray + 8);
    if (basePtr == NULL) return;

    int base = *basePtr;
    // in_EAX is the slot index (e.g., controller or network slot)
    int slotIndex; // Placeholder: this value comes from EAX register
    // The exact slot index is passed via EAX; in C cannot be expressed directly.
    // Assume slotIndex is known (e.g., from the calling context).
    unsigned char *targetByte = (unsigned char *)(base + slotIndex * 0x50 + 0x54 + *offsetPtr);
    *targetByte |= bitMask;
}