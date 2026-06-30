// FUNC_NAME: ObjectSystem::resolveDataPointer
int* __fastcall ObjectSystem::resolveDataPointer(int* objectPtr)
{
    // Check class ID at offset +6 (likely a magic number for a specific class)
    if (*(short*)((int)objectPtr + 6) != 0x25e3) {
        // Not the expected class; return pointer to data after header (offset 2 words)
        return objectPtr + 2;
    }
    // Expected class: if first field is non-zero, treat as offset from data pointer
    if (*objectPtr != 0) {
        // Return data pointer (objectPtr[2]) plus the offset stored at objectPtr[0]
        return (int*)(objectPtr[2] + *objectPtr);
    }
    // Fallback: return global sentinel (likely null or empty table)
    return (int*)0x0120e700;
}