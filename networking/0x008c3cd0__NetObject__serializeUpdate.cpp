// FUNC_NAME: NetObject::serializeUpdate
int __thiscall NetObject::serializeUpdate(int thisPtr, int buffer) {
    int currentOffset;
    int i;
    int* ptrArray;
    int count;
    int* writePtr;
    int* srcPtr;
    int size;

    // Get initial write offset from buffer (likely alignment or base)
    currentOffset = FUN_008c1850(buffer);
    writePtr = (int*)(buffer + currentOffset);

    // Serialize first array of object IDs (e.g., ghost list)
    if (*(int*)(thisPtr + 0x10c) != 0) {
        count = 0;
        ptrArray = *(int**)(thisPtr + 0x108);
        do {
            // Each entry is a pointer to an object; read its netID at offset 0x38
            *writePtr = *(int*)(*(int*)(ptrArray[count]) + 0x38);
            count++;
            writePtr++;
        } while (count < *(uint*)(thisPtr + 0x10c));
    }

    // Serialize second array of object IDs (e.g., dirty list)
    srcPtr = writePtr;
    if (*(int*)(thisPtr + 0x118) != 0) {
        count = 0;
        ptrArray = *(int**)(thisPtr + 0x114);
        do {
            *srcPtr = *(int*)(*(int*)(ptrArray[count]) + 0x38);
            count++;
            srcPtr++;
        } while (count < *(uint*)(thisPtr + 0x118));
    }

    // Serialize additional data blocks
    currentOffset = *(int*)(thisPtr + 0x118);
    size = FUN_008bfb00(srcPtr + currentOffset);
    writePtr = (int*)((int)(srcPtr + currentOffset) + size);
    size = FUN_008bfb90(writePtr);
    writePtr = (int*)((int)writePtr + size);
    size = FUN_008c1bb0(writePtr);
    writePtr = (int*)((int)writePtr + size);

    // Type-specific serialization (e.g., for player/vehicle)
    if (*(int*)(thisPtr + 0x54) == 0x637b907) {
        size = 0;
        if (*(int*)(thisPtr + 0x230) != 0) {
            size = FUN_00892760(writePtr);
        }
        writePtr = (int*)((int)writePtr + size);
    }

    // Return total bytes written
    return (int)writePtr - buffer;
}