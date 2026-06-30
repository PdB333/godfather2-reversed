// FUNC_NAME: BitStream::alignBufferSize
void __fastcall BitStream::alignBufferSize(void* thisPtr, BufferDescriptor* buffer, uint inputSize)
{
    // Preserve the low bit flag from the size field at offset +0x04
    uint flag = buffer->size & 1;

    // Clamp input size to maximum 80 (0x50)
    if (inputSize > 0x50)
        inputSize = 0x50;

    // Compute aligned size: add header size 11 (0x0b) then check minimum
    uint alignedSize = inputSize + 0x0b;
    if (alignedSize > 0x10)
    {
        // Align to 8 bytes, preserving the lowest bit (flag)
        buffer->size = (alignedSize & 0xfffffff8) | flag;
    }
    else
    {
        // Minimum allocation size is 16 (0x10), keep flag
        buffer->size = flag | 0x10;
    }
}