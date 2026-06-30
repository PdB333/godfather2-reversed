// FUNC_NAME: InternalData::copyToBuffer
void __thiscall InternalData::copyToBuffer(uint32_t *this, uint32_t *destBuffer) {
    uint32_t *srcPtr;
    uint32_t *dstPtr;
    int blocks;

    blocks = 2;
    srcPtr = *this;                     // this->m_pData (pointer to source data)
    dstPtr = destBuffer + 2;            // skip 8-byte header (2 dwords) at destBuffer start
    do {
        // Copy one 32-byte block (8 dwords) from source to destination
        dstPtr[-2] = srcPtr[0];
        dstPtr[-1] = srcPtr[1];
        dstPtr[0]  = srcPtr[2];
        dstPtr[1]  = srcPtr[3];
        dstPtr[2]  = srcPtr[4];
        dstPtr[3]  = srcPtr[5];
        dstPtr[4]  = srcPtr[6];
        dstPtr[5]  = srcPtr[7];
        srcPtr += 8;
        dstPtr += 8;
        blocks--;
    } while (blocks != 0);
    // Total 64 bytes (2 * 32) copied
}