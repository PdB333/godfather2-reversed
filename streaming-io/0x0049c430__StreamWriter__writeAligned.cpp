// FUNC_NAME: StreamWriter::writeAligned
void __thiscall StreamWriter::writeAligned(void* thisPtr, const void* src, size_t size, uint32_t alignment) {
    // Align the current buffer pointer to the next multiple of 'alignment' (must be power of two)
    // +0x14: current write pointer (m_curPtr)
    void* alignedDst = (void*)((uint32_t)(*(char**)((uint8_t*)thisPtr + 0x14)) + alignment - 1 & ~(alignment - 1));
    *(char**)((uint8_t*)thisPtr + 0x14) = (char*)alignedDst;

    // Copy the data into the aligned destination
    memcpy(alignedDst, src, size);

    // Advance the pointer past the written data, rounding up to the next 4-byte boundary
    *(char**)((uint8_t*)thisPtr + 0x14) = (char*)((uint32_t)(*(char**)((uint8_t*)thisPtr + 0x14)) + ((size + 3) & ~3));
}