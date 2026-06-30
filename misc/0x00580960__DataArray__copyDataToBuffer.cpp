// FUNC_NAME: DataArray::copyDataToBuffer
// Address: 0x00580960
// Role: Copies internal array data into an external buffer with a 16-byte header, 
//       but only if the internal capacity (stored as a short at +0x0A) is less than 
//       or equal to the requested max element count (param_2). Returns 1 on success, 0 on failure.
// The source object layout:
//   +0x00: vtable pointer (4 bytes)
//   +0x04-0x09: unknown (possibly other fields)
//   +0x0A: short capacity (max number of elements the array can hold)
//   +0x0C: int count (actual number of elements in use)
//   +0x10: int array[count] (inline, variable length)
// The output buffer receives:
//   +0x00: int unknown (set to 0)
//   +0x04: int unknown (set to 0)
//   +0x08: byte unknown (set to 1)
//   +0x09: byte unknown (set to 0)
//   +0x0A: short capacity (copied from source)
//   +0x0C: int count (copied from source)
//   +0x10: int array[count] (copied from source)

class DataArray {
public:
    // __thiscall method
    // @param outBuffer: destination buffer (must be at least 16 + count*4 bytes)
    // @param maxElements: maximum number of elements the caller expects (compared to capacity)
    // @return 1 if copy succeeded, 0 if capacity > maxElements
    int __thiscall copyDataToBuffer(uint32* outBuffer, uint32 maxElements) {
        // Access internal members via offset
        short* pCapacity = reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 0x0A);
        int* pCount = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x0C);
        uint32* pArray = reinterpret_cast<uint32*>(reinterpret_cast<char*>(this) + 0x10);

        // Validate: only copy if internal capacity <= requested maxElements
        if (*pCapacity > maxElements) {
            return 0; // failure – caller's buffer not large enough (by capacity)
        }

        // Write header to output buffer
        outBuffer[0] = 0;                               // offset +0x00: 4 bytes, unknown
        outBuffer[1] = 0;                               // offset +0x04: 4 bytes, unknown

        // Set byte at offset +0x08 to 1
        *reinterpret_cast<unsigned char*>(outBuffer + 2) = 1;  // outBuffer + 8 bytes

        // Set byte at offset +0x09 to 0
        *(reinterpret_cast<unsigned char*>(outBuffer) + 9) = 0; // direct byte access

        // Copy capacity (short) to output at offset +0x0A
        *reinterpret_cast<short*>(reinterpret_cast<char*>(outBuffer) + 0x0A) = *pCapacity;

        // Copy count (int) to output at offset +0x0C
        outBuffer[3] = *pCount;  // offset +0x0C (since each uint32 is 4 bytes)

        // Copy the array data starting at output offset +0x10 (outBuffer[4])
        memcpy(outBuffer + 4, pArray, *pCount * sizeof(uint32));

        return 1; // success
    }
};