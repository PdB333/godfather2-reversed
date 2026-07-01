// FUNC_NAME: PointerArray::clearAndFree
void __thiscall PointerArray::clearAndFree(PointerArray* this) {
    // this->count at +0x04, this->arrayBase at +0x00
    int count = this->count;
    int* arrayBase = this->arrayBase;

    // Iterate backwards over array of 8-byte elements
    for (int i = count - 1; i >= 0; i--) {
        // Each element is an 8-byte struct; first 4 bytes are a pointer (handle)
        int* element = reinterpret_cast<int*>(arrayBase + i * 8);
        if (*element != 0) {
            // Free the sub-object (likely a node or handle)
            subObjectDestructor(element); // FUN_004daf90
        }
    }

    // Free the array itself
    if (arrayBase != 0) {
        deallocateArray(arrayBase); // FUN_009c8f10
    }
}