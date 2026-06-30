// FUNC_NAME: SerialBuffer::writeVTableAndTwoVectors
// Address: 0x004e5790
// This function writes a vtable pointer, an int32, and two 128-bit aligned blocks
// into a buffer managed by the SerialBuffer object. The object's first field (offset 0x00) is a pointer
// to the actual buffer memory. Offset 0x14 within that buffer holds a write pointer that advances
// after each write. The 128-bit blocks are aligned to 16 bytes before storage.
typedef struct __declspec(align(16)) { uint64_t qword[2]; } Aligned128;

void __thiscall SerialBuffer::writeVTableAndTwoVectors(int* pBuffer, int32_t value, const Aligned128* vecA, const Aligned128* vecB) {
    // pBuffer is actually the this pointer; first field of the object points to the real buffer
    int* realBuffer = (int*)*pBuffer;                      // +0x00: pointer to internal buffer

    // Write vtable address at location pointed by write pointer (stored at buffer+0x14)
    *(int**)(*(int*)((char*)realBuffer + 0x14)) = &PTR_SomeVTable;  // PTR_LAB_01124ae0

    // Advance write pointer by 4 bytes
    *(int*)((char*)realBuffer + 0x14) += 4;

    // Write the integer 'value' at the new write location
    *(int*)(*(int*)((char*)realBuffer + 0x14)) = value;

    // Align write pointer to 16 bytes (round up)
    *(int*)((char*)realBuffer + 0x14) = 
        (int)(((uint32_t)(*(int*)((char*)realBuffer + 0x14)) + 0x13) & 0xFFFFFFF0);

    // Copy 16 bytes from vecA (first 128-bit block)
    Aligned128* dest = (Aligned128*)(*(int*)((char*)realBuffer + 0x14));
    dest->qword[0] = vecA->qword[0];
    dest->qword[1] = vecA->qword[1];

    // Align write pointer again for second block
    *(int*)((char*)realBuffer + 0x14) = 
        (int)(((uint32_t)(*(int*)((char*)realBuffer + 0x14)) + 0x13) & 0xFFFFFFF0);

    // Copy 16 bytes from vecB (second 128-bit block)
    dest = (Aligned128*)(*(int*)((char*)realBuffer + 0x14));
    dest->qword[0] = vecB->qword[0];
    dest->qword[1] = vecB->qword[1];

    // Advance write pointer by 16 bytes (0x10)
    *(int*)((char*)realBuffer + 0x14) += 0x10;
}
```