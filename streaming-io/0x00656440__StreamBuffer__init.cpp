// FUNC_NAME: StreamBuffer::init
// Function address: 0x00656440
// Initializes a stream buffer (likely for bit-level I/O). Sets up internal buffer,
// capacities, and calls virtual initialization.

void __thiscall StreamBuffer::init(void) {
    // Stack buffer for raw data (1024 bytes = 8192 bits)
    uint8_t m_buffer[1024];                 // local_400

    // Internal pointers and sizes
    uint8_t* m_bufferPtr = m_buffer;        // local_52c
    uint32_t m_maxCapacity = 0x2000;        // local_50c – max bits capacity
    uint32_t m_minCapacity = 0x2000;        // local_508 – min bits capacity (same)
    uint32_t m_flag1 = 0;                   // local_534
    uint32_t m_flag2 = 0;                   // local_530
    uint32_t m_writeSize = 0x400;           // local_528 – write size in bytes (1024)
    uint32_t m_bitOffset = m_bitOffset & 0xffffff00; // local_524 – align to 256 bits
    uint32_t m_someCounter = 0;             // local_520
    uint8_t m_alignByte1 = 0;               // local_51c
    uint8_t m_alignByte2 = 0;               // local_51b
    uint8_t m_reservedByte = 0;             // local_500
    uint32_t m_reservedFlag = 0;            // local_504

    // Pointer to a global vtable or base interface
    void** m_globalVtable = &PTR_LAB_00e42f38; // local_538

    // Alignment type for allocations (4-byte)
    uint8_t m_alignType = 4;                // local_53d

    // Allocate 8 bytes with alignment type (maybe an internal structure)
    FUN_0064b810(8, &m_alignType);

    // Read member at offset +0xA4 from this object (size or buffer length)
    uint32_t m_memberSize = *(uint32_t*)((uint8_t*)this + 0xA4); // in_EAX[0x29]
    // Allocate 0x20 bytes using that size – possibly a bitstream context
    FUN_0064b810(0x20, &m_memberSize);

    // Call virtual function at vtable offset 0x28 – likely a base-class init
    // passing the global vtable pointer as argument
    (*(void (**)(void*))(*((uint32_t*)this) + 0x28))(&m_globalVtable);

    // Copy from caller's stack frame (return address + 0x5C) to a small 4-byte buffer
    // Number of bytes = (m_bitOffset + 7) >> 3 (bitOffset rounded up to byte)
    // Last parameter = 1 (flag)
    FUN_00658230((void*)((uintptr_t)__builtin_return_address(0) + 0x5C), &m_alignByte1,
                 (m_bitOffset + 7) >> 3, 1);

    // Finalization (debug output, flush, etc.)
    FUN_0064b440();
}