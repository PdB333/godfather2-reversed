// FUNC_NAME: Buffer::assignConcat
void __thiscall Buffer::assignConcat(const void* buffer1, size_t size1, const void* buffer2, size_t size2)
{
    // Layout:
    // +0x00: char* data
    // +0x04: size_t length
    // +0x08: size_t capacity
    // +0x0C: void* deallocator (custom deleter function pointer)

    if (size1 == 0) {
        if (size2 != 0) {
            this->length = size2;
            this->capacity = size2;
            this->data = (char*)allocateMemory(size2 + 1);  // FUN_009c8e50
            this->deallocator = (void*)customDeallocator;   // thunk_FUN_009c8eb0
            _memcpy(this->data, buffer2, size2);
            this->data[this->length] = '\0'; // null-terminate
            return;
        }
        // Both empty: set to null/empty
        this->data = nullptr;
        this->capacity = 0;
        this->length = 0;
        return;
    }

    if (size2 != 0) {
        size_t totalSize = size1 + size2;
        this->length = totalSize;
        this->capacity = totalSize;
        this->data = (char*)allocateMemory(totalSize + 1);
        this->deallocator = (void*)customDeallocator;
        _memcpy(this->data, buffer1, size1);
        _memcpy(this->data + size1, buffer2, size2);
        this->data[this->length] = '\0';
        return;
    }

    // Only buffer1 is non-empty
    this->length = size1;
    this->capacity = size1;
    this->data = (char*)allocateMemory(size1 + 1);
    this->deallocator = (void*)customDeallocator;
    _memcpy(this->data, buffer1, size1);
    this->data[this->length] = '\0';
    return;
}