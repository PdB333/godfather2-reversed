// FUNC_NAME: SomeClass::copyFromSource

struct SomeClass {
    uint32_t* m_pData; // +0x08: destination buffer pointer
    uint32_t m_count;  // loaded into ESI before call
};

void __thiscall SomeClass::copyFromSource(uint32_t* src) {
    if (m_pData == nullptr || m_count == 0) {
        return;
    }
    for (uint32_t i = 0; i < m_count; ++i) {
        m_pData[i] = src[i];
    }
}