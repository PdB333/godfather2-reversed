// FUNC_NAME: CommandBuffer::prependCommandBlock

// Address: 0x00635dc0
// This function inserts a command block (a float count followed by a UID) at a given position
// in a dynamic binary buffer of 8-byte elements (tag + data). The buffer grows as needed.
// param_1: int numKeep – number of elements from the base to preserve before the insertion point.
// param_2: int basePtr – base address of the buffer (should equal this->bufferStart).
void CommandBuffer::prependCommandBlock(int numKeep, int basePtr) {
    int elemCount = (this->writePtr - basePtr) >> 3; // current number of elements written
    if (elemCount < numKeep) {
        int needZeros = numKeep - elemCount;
        if (this->bufferEnd - this->writePtr <= needZeros * 8) {
            this->grow(); // reallocate to larger capacity
        }
        elemCount = numKeep; // after filling zeros, count becomes numKeep
        do {
            *(int*)this->writePtr = 0;
            this->writePtr += 8;
            needZeros--;
        } while (needZeros != 0);
    }
    int shiftCount = elemCount - numKeep; // number of existing elements to move forward
    uint uid = this->allocateUID(shiftCount, 1);
    if (shiftCount > 0) {
        int offset = -shiftCount * 8;
        int remaining = shiftCount;
        do {
            uint* src = (uint*)(this->writePtr + offset);
            uint* dst = (uint*)this->getStaticSentinel();
            if (dst == &DAT_00e2a93c) {
                dst = (uint*)this->getDefaultSentinel();
            }
            offset += 8;
            *dst = *src;
            *(dst + 1) = *(src + 1);
            remaining--;
        } while (remaining != 0);
    }
    this->commitTags();
    uint* tagBuf = (uint*)this->beginWriteTag();
    *tagBuf = 3;           // tag type: float
    *(float*)(tagBuf + 1) = (float)shiftCount;
    this->writePtr += shiftCount * -8; // move back to insertion position
    uint* nextTag = (uint*)this->writePtr;
    *nextTag = 5;           // tag type: UID
    *(nextTag + 1) = uid;
    // Ensure remaining space for at least 9 elements
    if (this->bufferEnd - this->writePtr < 9) {
        int oldCap = this->capacity;
        int newCap = oldCap * 2;
        if (oldCap < 1) {
            newCap = oldCap + 0x15;
        }
        int newBuf = this->memRealloc(oldCap * 8, newCap * 8);
        this->bufferStart = newBuf;
        this->capacity = newCap;
        this->bufferEnd = newBuf - 0xa8 + newCap * 8; // offset 0xA8 likely for header
        this->reorderBuffers();
    }
    this->writePtr += 8;
}