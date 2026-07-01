// FUNC_NAME: GetOwnerFromBackPointer
// Function at 0x007a49d0: Retreives a pointer to a containing object from a back-pointer stored at offset +0x30A4.
// The back-pointer points to a sub-object; subtracting 0x48 yields the base of the parent object.
// Returns 0 if the back-pointer is null.
int GetOwnerFromBackPointer(void* componentPtr) {
    // Dereference back-pointer at offset 0x30A4
    int* backPtr = *(int**)((char*)componentPtr + 0x30A4);
    if (backPtr != 0) {
        // The back-pointer points into the parent object at offset 0x48
        return (int)((char*)backPtr - 0x48);
    }
    return 0;
}