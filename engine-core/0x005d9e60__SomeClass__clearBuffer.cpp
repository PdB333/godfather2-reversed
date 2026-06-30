// FUNC_NAME: SomeClass::clearBuffer
void SomeClass::clearBuffer() {
    // Fields accessed via this (in ESI):
    // +0x00: vtable pointer
    // +0x04: unknown
    // +0x08: m_pBufferStart (pointer to beginning of allocated array)
    // +0x0C: m_nElementCount (number of valid elements in buffer)
    // +0x10: m_pBufferEnd (pointer to one past last allocated element)

    int *startPtr = *(int **)(this + 0x08);  // unaff_ESI[2]
    if (startPtr != 0) {
        int *endPtr = *(int **)(this + 0x10); // unaff_ESI[4]
        // Calculate size to free: number of whole elements (0x28 bytes each) from start to end
        int numBytes = ((int)endPtr - (int)startPtr) / 0x28 * 0x28;
        // Call virtual deallocation function (vtable at +0x04)
        void (*deallocFunc)(void *, int) = *(void (**)(void *, int))(*(int *)this + 4);
        deallocFunc(startPtr, numBytes);
    }
    // Reset buffer state
    *(int **)(this + 0x08) = 0;   // m_pBufferStart = null
    *(int *)(this + 0x0C) = 0;    // m_nElementCount = 0
    *(int **)(this + 0x10) = 0;   // m_pBufferEnd = null
    return;
}