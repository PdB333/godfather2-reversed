// FUNC_NAME: clearObjectWithSubPointer
// Function at 0x004a93a0
// Clears a main object (0x80 bytes) and a sub-object pointed to at offset +0x10 (0x20 bytes)

void clearObjectWithSubPointer(void* objectPointer)
{
    // Clear the main structure (128 bytes from objectPointer)
    clearMemory(0x80, objectPointer);

    // Retrieve pointer to sub-object at offset +0x10
    void* subObjectPtr = *(void**)((int)objectPointer + 0x10);

    // Clear the sub-object (32 bytes)
    clearMemory(0x20, subObjectPtr);
}