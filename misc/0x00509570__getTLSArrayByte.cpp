// FUNC_NAME: getTLSArrayByte
unsigned char getTLSArrayByte(int slotIndex, int* subOffset) {
    // Access TEB->ThreadLocalStoragePointer at FS:[0x2C]
    void** tlsSlotArray = (void**)__readfsdword(0x2C);
    // First TLS slot (index 0) holds a per‑thread structure
    void* perThreadData = *tlsSlotArray;
    // Offset +8 in that structure contains a base pointer for an array
    char* arrayBase = *(char**)((char*)perThreadData + 8);
    // Each element is 0x50 bytes; final offset is 0x55 + *subOffset
    char* target = arrayBase + slotIndex * 0x50 + 0x55 + *subOffset;
    return *(unsigned char*)target;
}