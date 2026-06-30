// FUNC_NAME: DataWriter::writeAlignedSIMDBlock
// Address: 0x004e8760
// Role: Writes a 4-byte header and four 16-byte SIMD values (e.g., 4x4 matrix or quaternion + vector) into an aligned stream buffer.
// The buffer pointer is stored at +0x14 of the object. After writing the header, subsequent 16-byte writes are aligned to 16-byte boundaries
// using non-standard rounding (0x13 and 0x1f masks), likely to enforce a specific memory layout for SIMD operations.

class DataWriter {
public:
    // +0x14: current write pointer into a dynamically allocated or pre-initialized buffer
    uint8_t* mWritePtr;

    // Writes a 32-bit header followed by four __m128 values with alignment
    void writeAlignedSIMDBlock(uint32_t header, const __m128& vec0, const __m128& vec1, const __m128& vec2, const __m128& vec3) {
        // Store 4-byte integer at current position
        *(uint32_t*)mWritePtr = header;

        // Align pointer to next 16-byte boundary (using +0x13 to skip up to 3 bytes before alignment)
        mWritePtr = (uint8_t*)(((uintptr_t)mWritePtr + 0x13) & ~0xF);

        // Write first 16-byte SIMD vector
        *(__m128*)mWritePtr = vec0;
        mWritePtr = (uint8_t*)(((uintptr_t)mWritePtr + 0x1F) & ~0xF); // align again

        // Write second vector
        *(__m128*)mWritePtr = vec1;
        mWritePtr = (uint8_t*)(((uintptr_t)mWritePtr + 0x1F) & ~0xF);

        // Write third vector
        *(__m128*)mWritePtr = vec2;
        mWritePtr = (uint8_t*)(((uintptr_t)mWritePtr + 0x1F) & ~0xF);

        // Write fourth vector
        *(__m128*)mWritePtr = vec3;

        // Final advancement by 16 bytes (no alignment)
        mWritePtr += 0x10;
    }
};