// FUNC_NAME: EventBuffer::writeStateChange
void EventBuffer::writeStateChange(void)
{
    int* sourcePtr;        // piVar3
    int* writePos;         // puVar1
    int writeAddr;         // iVar2

    // Check if there is pending source data at the given offset
    if (this->m_sourceOffset != 0) {
        // Calculate pointer to current source data entry (two ints: type and value)
        sourcePtr = (int*)(this->m_sourceBase + this->m_sourceOffset);

        // Only process entries with type tag 6
        if (*sourcePtr == 6) {
            // Get current write position in the destination buffer
            writePos = (int*)this->m_writePos;

            // Shift forward the two ints currently at writePos (overwrite with previous values)
            *writePos = writePos[-2];
            writePos[1] = writePos[-1];

            // Now write the new source data (type and value) into the positions we just vacated
            writeAddr = (int)this->m_writePos;
            *(int*)(writeAddr - 8) = *sourcePtr;      // type tag
            *(int*)(writeAddr - 4) = sourcePtr[1];    // data

            // Ensure there is enough remaining buffer space for the next write (9 bytes min?)
            if ((int)this->m_bufferEnd - (int)this->m_writePos < 9) {
                this->growBuffer();
            }

            // Advance write pointer by 8 bytes
            this->m_writePos = (char*)this->m_writePos + 8;

            // Notify that a new state has been written (process callback)
            this->onWriteComplete();
        }
        else {
            // Unknown type – skip and call cleanup
            this->advanceSourceOffset();
            return;
        }
    }
    // No pending source data – finalize or skip
    this->advanceSourceOffset();
}