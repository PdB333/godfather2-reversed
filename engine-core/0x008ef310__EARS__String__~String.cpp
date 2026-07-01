//FUNC_NAME: EARS::String::~String
void __fastcall EARS::String::~String(int this)
{
    // +0x04: m_pData (pointer to string data)
    // +0x08: m_nLength (length of string, or another pointer)
    char localBuffer[8]; // Temporary buffer for small string optimization or backup

    // Copy string data into local buffer (possibly for small string optimization)
    FUN_008ee5b0(localBuffer, this, **(int**)(this + 4), this, *(int**)(this + 4));

    // Release the allocated string data
    FUN_009c8eb0(*(int*)(this + 4));

    // Null out the pointer and length
    *(int*)(this + 4) = 0;
    *(int*)(this + 8) = 0;
}