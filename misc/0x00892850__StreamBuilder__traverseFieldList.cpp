// FUNC_NAME: StreamBuilder::traverseFieldList

// Function at 0x00892850
// Reconstructed C++ for traversing a list of three field descriptors and computing end offset.
int StreamBuilder::traverseFieldList(char* thisPtr, int streamParam) // __thiscall
{
    int fieldSize;
    int currentOffset;

    // +0x20: offset to an integer index (e.g., field count or list index)
    // +0x30: base of an array of 4-byte offsets/pointers to descriptors
    // Multiply index by 4 because array elements are 4 bytes.
    currentOffset = (int)(thisPtr + 0x30 + (*(int*)(thisPtr + 0x20)) * 4);

    // Process first descriptor: returns its size/advance
    fieldSize = processField((char*)currentOffset, streamParam);
    currentOffset += fieldSize;

    // Process second descriptor
    fieldSize = processField((char*)currentOffset, streamParam);
    currentOffset += fieldSize;

    // Process third descriptor
    fieldSize = processField((char*)currentOffset, streamParam);

    // Return total offset from this to end of the third descriptor
    // (currentOffset - this) is the start of the third descriptor,
    // adding fieldSize gives end offset.
    return fieldSize + (currentOffset - (int)thisPtr);
}