// FUNC_NAME: 0x004d3bc0: String::String(const char* str)
// reconstructs a custom string class (16 bytes) with embedded deallocator function pointer
// offsets: +0x0 = m_pBuffer (char*), +0x4 = m_nLength (int), +0x8 = m_nAllocated (int), +0xC = m_pDeallocator (void(*)(void*))
// calls custom allocator at 0x009c8e50 and stores deallocator thunk at 0x009c8eb0

int* __thiscall String::String(const char* str) {
    char c;
    const char* p;
    int len;
    void* newBuffer;

    if (str != nullptr && *str != '\0') {
        // calculate length of input string
        p = str;
        do {
            c = *p;
            p++;
        } while (c != '\0');
        len = (int)(p - (str + 1)); // length excluding null terminator

        // set length and capacity
        this->m_nLength = len;
        this->m_nAllocated = len;

        // allocate memory for the string (len+1 bytes for null terminator)
        newBuffer = allocateMemory(len + 1);  // FUN_009c8e50 is memory allocator

        this->m_pBuffer = (char*)newBuffer;

        // copy string content
        memcpy(newBuffer, str, this->m_nLength);

        // null terminate
        *(char*)((int)this->m_pBuffer + this->m_nLength) = '\0';

        // store deallocator function pointer
        this->m_pDeallocator = (void(*)(void*))thunk_FUN_009c8eb0; // custom deallocator

        return this;
    }

    // empty string or null: zero out fields
    this->m_pBuffer = nullptr;
    this->m_nAllocated = 0;
    this->m_nLength = 0;
    return this;
}