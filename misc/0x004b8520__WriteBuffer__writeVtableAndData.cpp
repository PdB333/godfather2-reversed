// FUNC_NAME: WriteBuffer::writeVtableAndData

void __thiscall WriteBuffer::writeVtableAndData(int* this, int data, char flag)
{
    // 'this' points to a serialization buffer object.
    // First field (offset 0) is a pointer to a buffer header.
    int* bufferHeader = *this;        // +0x00: pointer to buffer header

    // The buffer header contains a write pointer at offset 0x14.
    // Write pointer is a pointer to the next free location in the raw buffer.
    int** writePtr = (int**)(bufferHeader + 0x14 / 4); // +0x14: current write pointer

    // Write a vtable pointer (type identifier) to the buffer.
    **(int***)writePtr = (int*)&PTR_LAB_011246f4;   // Write vtable pointer for some class
    *writePtr = *writePtr + 1;                       // Advance writePtr by 4 bytes (sizeof(int))

    // Write a 4-byte integer (param_2) to the buffer.
    **(int***)writePtr = data;
    *writePtr = *writePtr + 1;                       // Advance writePtr by 4 bytes

    // Write a 1-byte flag (param_3) to the buffer.
    **(char***)writePtr = flag;
    // Advance write pointer by 1 byte, then align to next 4-byte boundary.
    *writePtr = (int*)(((unsigned int)(*writePtr + 1) + 3) & ~3);

    // Store the updated write pointer back into the buffer header.
    bufferHeader[0x14 / 4] = (int)writePtr;
}