// FUNC_NAME: String::assignChar
void __thiscall String::assignChar(char c) // 0x004d3f90
{
    // +0x00: char* m_pData;      // pointer to allocated character buffer
    // +0x04: int   m_nLength;    // length of string (number of characters, excluding null)
    // +0x08: int   m_nState;     // 0=uninitialized, 1=allocated with our own buffer, 2=external/readonly
    // +0x0C: void (*m_pDeallocator)(char*);  // function pointer to deallocate buffer

    if (this->m_nState < 2) // if buffer is not readonly
    {
        if (this->m_pData != nullptr) // free old buffer
        {
            this->m_pDeallocator(this->m_pData);
        }
        // allocate new buffer of size 2 (one char + null terminator)
        this->m_pData = FUN_009c8e50(2);
        this->m_nState = 1;
        this->m_pDeallocator = thunk_FUN_009c8eb0; // standard deallocation function
    }
    // write the character and null terminator
    this->m_pData[0] = c;
    this->m_pData[1] = '\0';
    this->m_nLength = 1;
}