// FUNC_NAME: PacketBuffer::getDataPointer
int PacketBuffer::getDataPointer(void)
{
    // +0x00: pointer to the actual packet buffer (may be null if not allocated)
    int *bufferObjPtr = (int *)getBufferObject(this);
    if (*bufferObjPtr != 0) {
        // Return pointer to data region, skipping 8-byte header
        return *bufferObjPtr + 8;
    }
    return 0;
}