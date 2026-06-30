// FUNC_NAME: SetThreadLocalFlag
// Address: 0x005094c0
// Role: Sets a bit in a thread-local byte array based on an index and offset.
// Uses FS segment to access thread-local storage (TLS). The index (passed in EAX) selects a slot of size 0x50.
// The offset (*param_1) selects a byte within that slot, then param_2 is ORed into that byte.

void SetThreadLocalFlag(int* offset, byte bitMask)
{
    // Retrieve TLS base from FS:[0x2c] (standard EA thread-local storage)
    // This is typically the TIB (Thread Information Block) or a custom TLS block.
    // Dereference twice: get pointer to TLS base, then get pointer to the array base.
    int* tlsBase = *(int**)(*(int*)(__readfsdword(0x2c)) + 8);
    // Compute byte address: index (in EAX assumed) * 0x50 + 0x54 + *offset
    // in_EAX is the global register variable that holds the current thread index?
    // Actually it's the value that was in EAX at function entry. We'll assume it's an implicit parameter.
    // For clarity, we'll declare it as an extern register variable to match the compiled code.
    register int index; // in EAX
    __asm mov index, eax;
    
    byte* targetByte = (byte*)(tlsBase + index * 0x50 + 0x54 + *offset);
    *targetByte |= bitMask;
}