// FUNC_NAME: StreamBuffer::writePackedValues
// Address: 0x004f2100
// Role: Writes a packed sequence of values with alignment into a stream buffer.
// The buffer is pointed to by the object's internal data at offset 0x14.
// Writes a vtable pointer, then four 4-byte values with 4-byte alignment,
// then an 8-byte value (from two 4-byte parameters), then a final 4-byte value.

void __thiscall StreamBuffer::writePackedValues(int* thisPtr, int param2, int param3, int param4, int param5, int param6, int param7)
{
    int* internalData = *thisPtr; // Dereference this to get internal data pointer (offset 0)
    int* writePtr; // Current write pointer in buffer

    // Write the vtable pointer (PTR_FUN_01124d8c) at current buffer position
    *(int**)(internalData + 0x14) = &PTR_FUN_01124d8c;
    writePtr = (int*)(internalData + 0x14);
    *writePtr = *writePtr + 4; // Advance buffer pointer by 4

    // Write param2 (no alignment before it)
    *(int*)(internalData + 0x14) = param2;
    // Align to next 4-byte boundary after writing param2
    writePtr = (int*)((*(int*)(internalData + 0x14) + 7) & 0xFFFFFFFC);
    *(int**)(internalData + 0x14) = writePtr;
    *writePtr = param3; // Write param3 at aligned address

    // Align again for param4
    writePtr = (int*)((*(int*)(internalData + 0x14) + 7) & 0xFFFFFFFC);
    *(int**)(internalData + 0x14) = writePtr;
    *writePtr = param4; // Write param4

    // Align for 8-byte value (combining param6 and param7)
    writePtr = (int*)((*(int*)(internalData + 0x14) + 7) & 0xFFFFFFFC);
    *(int**)(internalData + 0x14) = writePtr;
    // Write 8-byte value: low 4 bytes = param6, high 4 bytes = param7
    *(long long*)((int*)(internalData + 0x14)) = (long long)param6 | ((long long)param7 << 32);
    // Advance buffer pointer by 8
    *(int*)(internalData + 0x14) = *(int*)(internalData + 0x14) + 8;

    // Write param5 at current buffer position, then advance by 4
    *(int*)(internalData + 0x14) = param5;
    *(int*)(internalData + 0x14) = *(int*)(internalData + 0x14) + 4;
}