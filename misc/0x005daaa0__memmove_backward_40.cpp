// FUNC_NAME: memmove_backward_40
// Address: 0x005daaa0
// Reconstructed C++ for copying 40-byte blocks in reverse order (overlap-safe backward move).
// The function copies 5 qwords (40 bytes) from source (param_1) to destination (EAX) while decrementing pointers by 0x28.
// param_2 is the lower bound for the source pointer.

void __thiscall memmove_backward_40(void *srcPtr, void *srcEnd)
{
    uint64_t *dest = (uint64_t *)srcPtr;  // EAX register holds the destination address in the original asm
    uintptr_t src = (uintptr_t)srcPtr;
    uintptr_t end = (uintptr_t)srcEnd;

    while (src != end)
    {
        // Copy 5 qwords (40 bytes) from src-0x28 to dest-0x28
        dest[-5] = *(uint64_t *)(src - 0x28);
        dest[-4] = *(uint64_t *)(src - 0x20);
        dest[-3] = *(uint64_t *)(src - 0x18);
        dest[-2] = *(uint64_t *)(src - 0x10);
        dest[-1] = *(uint64_t *)(src - 0x08);

        dest -= 5;       // Move destination back by 40 bytes
        src -= 0x28;     // Move source back by 40 bytes
    }
    return;
}