// FUNC_NAME: BufferManager::allocateBuffer

int __thiscall BufferManager::allocateBuffer(int count)
{
    void *buffer = customAlloc(count * 16, 0x40000); // 0x40000 = allocation flag (heap type/alignment)
    this->bufferPtr = buffer; // +0x58
    if (buffer != nullptr) {
        memset(buffer, 0, count * 16);
        this->capacity = count; // +0x54
        this->usedCount = 0; // +0x50
        return 1;
    }
    return 0;
}