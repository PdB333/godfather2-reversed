// FUNC_NAME: DataBuffer::pushElement
void __thiscall DataBuffer::pushElement(int sourceIndex) {
    undefined4* pWritePos;
    undefined4* pSrc;

    if (sourceIndex > 0) {
        // Copy element from buffer at index (sourceIndex - 1) to current write position
        pWritePos = *(undefined4**)(this + 8);          // m_pWritePos at +0x08
        pSrc = (undefined4*)(*(int*)(this + 0x0C) + (sourceIndex - 1) * 8);  // m_pBufferBase + (sourceIndex-1)*8
        *pWritePos = *pSrc;
        pWritePos[1] = pSrc[1];
        *(int*)(this + 8) = *(int*)(this + 8) + 8;     // Advance write pointer
        return;
    }
    // sourceIndex <= 0: use default element from helper function
    pWritePos = (undefined4*)FUN_00625430();           // getDefaultElement() – returns pointer to default data
    pSrc = *(undefined4**)(this + 8);                  // current write position
    *pSrc = *pWritePos;
    pSrc[1] = pWritePos[1];
    *(int*)(this + 8) = *(int*)(this + 8) + 8;
}