// FUNC_NAME: pushInputEventToBuffer
void pushInputEventToBuffer(unsigned char inputByte) {
    // Get a specific per-thread structure pointer (FS:[0x2c]).
    int* threadStruct = *(int**)(__readfsdword(0x2c));
    // Check if a member at offset 0x34 in that structure is zero.
    if (*(int*)((char*)threadStruct + 0x34) == 0) {
        // Buffer pointer base (global) with offset 0x14 points to a "current write" pointer.
        char* bufferBase = (char*)DAT_01206880;
        int** currentSlotPtr = (int**)(bufferBase + 0x14);  // address holding the write pointer
        // Write vtable pointer of a specific command type into the current slot.
        **currentSlotPtr = (int*)&PTR_LAB_01124c34;
        // Advance the write pointer by 4 bytes (size of vtable pointer).
        int* currentPointer = *currentSlotPtr;
        *currentSlotPtr = (int*)((char*)currentPointer + 4);
        // Write the input byte as a uint in the next 4 bytes.
        *(unsigned int*)(*currentSlotPtr) = (unsigned int)inputByte;
        // Advance the write pointer by another 4 bytes (size of data).
        currentPointer = *currentSlotPtr;
        *currentSlotPtr = (int*)((char*)currentPointer + 4);
        return;
    }
    // Fallback: store directly into a global byte.
    DAT_012054fe = inputByte;
}