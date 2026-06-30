// FUNC_NAME: getTlsGlobalPointer
// Retrieves a 32-bit value from thread-local storage.
// Reads from FS segment: first gets the TLS array pointer (FS:[0x2C]),
// then dereferences to get the TLS data block pointer (index 0),
// then reads the 4-byte value at offset 0x24 within that block.
// This value is commonly a pointer to a per-thread global game state object.
unsigned int getTlsGlobalPointer()
{
    // Get the pointer to the TLS array from the TEB (FS segment offset 0x2C)
    unsigned int **tlsArray = reinterpret_cast<unsigned int **>(__readfsdword(0x2C));
    // The first element of the TLS array points to the actual TLS data block
    unsigned int *tlsDataBlock = *tlsArray;
    // Return the value at offset 0x24 (36 bytes into the TLS data block)
    return *(reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(tlsDataBlock) + 0x24));
}