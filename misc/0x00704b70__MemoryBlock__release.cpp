// FUNC_NAME: MemoryBlock::release
struct MemoryBlock {
    /* +0x13C */ uint32_t m_size;      // size of allocated data
    /* +0x140 */ void* m_pData;        // pointer to allocated memory block
};

void __thiscall MemoryBlock::release() {
    if (m_pData != nullptr) {
        // Deallocate the memory block (likely a heap free)
        FUN_009c8f10(m_pData);  // release function – could be operator delete or custom dealloc
        m_pData = nullptr;
        m_size = 0;
    }
}