// FUNC_NAME: NetConnection::ensureBufferAllocated
void __thiscall NetConnection::ensureBufferAllocated(void)
{
    // +0x210: pointer to a 0x1000-byte buffer
    if (this->bufferPointer == 0) {
        this->bufferPointer = heapAllocate(0x1000);
        if (this->bufferPointer) {
            // Zero-initialize the buffer in 4-byte chunks
            for (int i = 0; i < 0x1000; i += 4) {
                *(int *)((int)this->bufferPointer + i) = 0;
            }
        }
    }
}