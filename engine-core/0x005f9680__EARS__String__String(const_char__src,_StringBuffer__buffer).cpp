// FUNC_NAME: EARS::String::String(const char* src, StringBuffer* buffer)
int EARS::String::String(int this, StringBuffer* pBuffer, const char* src) {
    StringBuffer* buffer = pBuffer;
    pBuffer->addRef();  // vtable[2] (offset 0x8)
    int length;
    if (src == nullptr) {
        length = 0;
    } else {
        length = strlen(src, buffer);
    }
    allocateBuffer(buffer, length);  // FUN_005f9e00
    this->m_pBuffer = pBuffer;
    pBuffer->addRef();
    if (src != nullptr) {
        int newLength = strlen(src, this->m_pBuffer);
        this->m_nLength = newLength;
        pBuffer->setData(src, 0);  // vtable[1] (offset 0x4), copies src into buffer
        pBuffer->finalize();       // vtable[3] (offset 0xc)
        return this;
    }
    this->m_nLength = 0;
    pBuffer->finalize();
    return this;
}