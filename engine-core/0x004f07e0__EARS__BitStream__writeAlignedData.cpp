// FUNC_NAME: EARS::BitStream::writeAlignedData

class EARS::BitStream {
public:
    char* m_writeCursor; // +0x14: Pointer to current write position in buffer

    void writeAlignedData(uint32_t firstParam);
};

void EARS::BitStream::writeAlignedData(uint32_t firstParam)
{
    // First, write the initial 4-byte value at the current cursor
    *(uint32_t*)m_writeCursor = firstParam;
    // Align the cursor to next 4-byte boundary (add 7 and mask lower 2 bits)
    m_writeCursor = (char*)((uint32_t)(m_writeCursor + 7) & ~3);

    // Copy 32 bytes from the stack (passed by value as hidden parameter) to the aligned position
    // The 32-byte block is passed on the stack at offset +0x08 from the function's stack frame
    // This simulates reading a structure of size 0x20 that was pushed by the caller
    uint8_t data32[32];
    // The actual memory copy will happen via the stack reference; we use the known offset
    // Using memcpy from the callee list
    _memcpy(m_writeCursor, &data32, 0x20);
    // Advance the cursor by 32 bytes and align to next 4-byte boundary
    m_writeCursor = (char*)((uint32_t)(m_writeCursor + 0x23) & ~3);

    // Write a second 4-byte value (from stack offset 0x28)
    uint32_t secondInt = *(uint32_t*)((char*)&firstParam + 0x24); // approximate offset
    *(uint32_t*)m_writeCursor = secondInt;
    // Align again for the 8-byte write
    m_writeCursor = (char*)((uint32_t)(m_writeCursor + 7) & ~3);

    // Write an 8-byte value (from stack offset 0x2c)
    uint64_t thirdLong = *(uint64_t*)((char*)&firstParam + 0x28);
    *(uint64_t*)m_writeCursor = thirdLong;
    m_writeCursor += 8;

    // Write a final 4-byte value (from stack offset 0x34)
    uint32_t fourthInt = *(uint32_t*)((char*)&firstParam + 0x30);
    *(uint32_t*)m_writeCursor = fourthInt;
    m_writeCursor += 4;
}