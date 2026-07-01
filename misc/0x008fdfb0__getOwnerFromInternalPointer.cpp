// FUNC_NAME: getOwnerFromInternalPointer
int __fastcall getOwnerFromInternalPointer(void* obj) {
    // Read pointer at offset +0xC8 (200 decimal) from this object
    int* internalPtr = *(int**)((char*)obj + 0xC8);
    if (internalPtr != nullptr) {
        // Subtract 0x48 (72) to get the containing object's base address
        // This is a common pattern to retrieve the owner from a component pointer
        // that is offset from its container by 0x48 bytes.
        return (int)(internalPtr - 0x48); // Return as int (pointer)
    }
    return 0;
}