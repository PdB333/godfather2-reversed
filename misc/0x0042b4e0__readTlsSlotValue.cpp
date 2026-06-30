// FUNC_NAME: readTlsSlotValue
int readTlsSlotValue(int index)
{
    // FS:[0x2c] holds the base of thread-local storage (TLS) block
    // Dereference to get a pointer to an array of shorts (TLS slots)
    // The high 16 bits of that pointer are returned as the upper half of the result
    // The lower half comes from the short at offset 0x10 + index*2 inside the array
    int* tlsBase = *(int**)(__readfsdword(0x2c)); // read DWORD at FS:0x2c, treat as pointer to pointer
    int* slotArray = (int*)*tlsBase;              // first element of TLS block is pointer to slot array
    short lower = *(short*)((char*)slotArray + 0x10 + index * 2);
    short upper = (short)((uint)(int)slotArray >> 16);
    return (int)(((uint)upper << 16) | (uint)(unsigned short)lower);
}