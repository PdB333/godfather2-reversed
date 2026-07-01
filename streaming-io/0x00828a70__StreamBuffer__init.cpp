// FUNC_NAME: StreamBuffer::init
// Function address: 0x00828a70
// Role: Initializes a stream buffer structure. Sets a flag to 0 and conditionally calls a release function if count > 1.

void __fastcall StreamBuffer::init(void)
{
    // Call initialization function with data pointer and count
    // +0x04: m_pData (void*)
    // +0x08: m_count (int)
    FUN_008285c0(this->m_pData, this->m_count);

    // Clear flags field
    // +0x0C: m_flags (int)
    this->m_flags = 0;

    // If count > 1, release the data (e.g., free memory or decrement reference)
    if (this->m_count > 1) {
        FUN_009c8f10(this->m_pData);
    }
}