// FUNC_NAME: clearDynamicArray
// Function address: 0x0047a040
// Role: Clears a dynamic array stored in a struct. Iterates over each 0xc-byte element (calling a destructor) and then frees the memory block (which has a 4-byte header before the array). Zeroes the count and pointer fields.
// Embedded struct offsets:
//   +0x58 : pointer to array of elements (int*)
//   +0x5c : element count (uint8_t)

void clearDynamicArray(void) {
    char* const base = (char*)this;                      // this as byte pointer for offset arithmetic
    int* pArray = *(int**)(base + 0x58);                 // pointer to first element (each 0xc bytes)
    uint8_t count = *(uint8_t*)(base + 0x5c);            // number of elements

    // Call per-element destructor for each element
    for (uint8_t i = 0; i < count; ++i) {
        int elementAddr = (int)((char*)pArray + i * 0xc);
        FUN_00408310(elementAddr);                       // destructor for element (0xc-sized structure)
    }

    // Free the allocated memory block (header 4 bytes before array pointer)
    if (pArray != nullptr) {
        int headerAddr = (int)((char*)pArray - 4);
        FUN_009c8f10(headerAddr);                        // deallocate memory with header
    }

    // Reset fields
    *(uint8_t*)(base + 0x5c) = 0;
    *(int**)(base + 0x58) = nullptr;
}