// FUNC_NAME: BufferManager::BufferManager
void __thiscall BufferManager::BufferManager(void)
{
    // +0x00: m_pBuffer (pointer to allocated array)
    // +0x04: m_count (number of elements, 0x101 = 257)
    // +0x08: m_field8 (unused/zero)
    // +0x0C: m_fieldC (unused/zero)
    // +0x10: m_field10 (unused/zero)
    // +0x14: m_initialized (byte, set to 1)
    this->m_count = 0x101;
    this->m_pBuffer = 0;
    this->m_field8 = 0;
    this->m_fieldC = 0;
    this->m_field10 = 0;
    this->m_initialized = 1;

    // Allocate buffer for 257 32-bit values (0x404 bytes)
    void* buffer = MemAlloc(0x404);
    this->m_pBuffer = buffer;
    _memset(buffer, 0, this->m_count * 4);

    // Additional initialization
    initSubFunction(); // FUN_004e0d90
}