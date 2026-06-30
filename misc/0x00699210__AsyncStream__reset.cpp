// FUNC_NAME: AsyncStream::reset
// Function at 0x00699210: Resets the stream state, closes handle, releases sub-objects.
// Class likely AsyncStream (EA EARS engine stream wrapper).

void __fastcall AsyncStream::reset()
{
    // Close the handle if valid (0xffffffff is invalid sentinel)
    if (m_hHandle != (HANDLE)0xffffffff)
    {
        CloseHandle(m_hHandle);
        m_hHandle = (HANDLE)0xffffffff;
    }

    // Reset state fields
    m_state = 0;          // +0x00
    m_flags = 0;          // +0x1c (offset 7)
    m_count = 1;          // +0x20 (offset 8)
    m_offset = 0;         // +0x24 (offset 9)
    m_size = 0;           // +0x28 (offset 10)

    // Release sub-objects (mutually exclusive: either m_pSubObject2 or m_pSubObject1 is active)
    if (m_pSubObject2 == nullptr) // +0x2c (offset 11)
    {
        if (m_pSubObject1 != nullptr) // +0x14 (offset 5)
        {
            FUN_009c8eb0(m_pSubObject1); // release read buffer?
        }
    }
    else
    {
        FUN_009c8f10(m_pSubObject2); // release write buffer?
        m_pSubObject2 = nullptr;
    }
    m_pSubObject1 = nullptr;

    // Final reset
    m_someInt1 = 0;       // +0x30 (offset 12)
    m_anotherPointer = m_somePointer; // +0x08 (offset 2) = +0x04 (offset 1)
    m_someInt2 = 0;       // +0x34 (offset 13)
}