// FUNC_NAME: Allocator::allocateZeroedBuffer
void __thiscall Allocator::allocateZeroedBuffer(size_t size, BufferInfo* outInfo) {
    // Allocate via virtual method at vtable+0x28 (likely a custom allocator)
    int unusedFlag = 0; // flag passed to allocator, possibly unused
    void* buffer = (this->allocateFunction)(size, &unusedFlag); // vtable entry at offset 0x28
    memset(buffer, 0, size);
    // Store pointer and size into output struct
    outInfo->buffer = buffer; // +0x00
    outInfo->size = size;     // +0x04
}