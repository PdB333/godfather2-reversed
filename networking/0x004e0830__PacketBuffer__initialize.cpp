// FUNC_NAME: PacketBuffer::initialize
void PacketBuffer::initialize(void)
{
    // This is a member function, 'this' pointer in EAX.
    // Set buffer count to 257 (0x101) entries, each 4 bytes.
    this->m_entryCount = 0x101;           // +0x04: number of entries (dwords)
    this->m_pBuffer = 0;                  // +0x00: pointer to allocated buffer
    this->m_field8 = 0;                   // +0x08
    this->m_fieldC = 0;                   // +0x0C
    this->m_field10 = 0;                  // +0x10
    *(uint8_t*)((uint8_t*)this + 0x14) = 1; // +0x14: flag byte = 1

    // Allocate buffer: m_entryCount * sizeof(uint32) = 0x404 bytes
    void* buffer = (void*)heapAlloc(0x404); // FUN_009c8e80: custom allocator
    this->m_pBuffer = buffer;               // +0x00

    // Clear the allocated memory
    memset(buffer, 0, this->m_entryCount * 4);

    // Call additional initialization (likely sets up virtual tables or other fields)
    someInitFunction(); // FUN_004e0d90
}