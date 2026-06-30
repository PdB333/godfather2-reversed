// FUNC_NAME: BitStream::writeHashBlock
// Address: 0x006368c0
// Writes a block consisting of a constant type (4) and a hash of the provided string.
// If remaining buffer space is less than 9 bytes, calls enlargeBuffer() to grow.
void __thiscall BitStream::writeHashBlock(const char* str)
{
    // Current write pointer at +0x8, buffer end at +0x18
    uint32_t* cur = reinterpret_cast<uint32_t*>(mWritePtr); // +0x8: mWritePtr (byte pointer)
    *cur = 4; // Block type identifier
    // Scan string to null terminator (side effect, hash function uses it)
    const char* p = str;
    while (*p != '\0') {
        ++p;
    }
    // Compute hash of the input string
    uint32_t hash = computeStringHash(str); // FUN_00638920
    *(cur + 1) = hash; // Write 32-bit hash after type
    // Ensure we have at least 9 bytes left (8 written + 1 for safety)
    if ((mBufferEnd - mWritePtr) < 9) { // +0x18: mBufferEnd
        enlargeBuffer(); // FUN_00635c70
    }
    mWritePtr += 8; // Advance write pointer by 2 dwords
}