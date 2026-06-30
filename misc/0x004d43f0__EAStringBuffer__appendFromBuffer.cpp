// FUNC_NAME: EAStringBuffer::appendFromBuffer

struct EAStringBuffer {
    char* buffer;          // +0x00: pointer to data
    int length;            // +0x04: current usage length (excluding null)
    int capacity;          // +0x08: allocated capacity
    void (*deallocFunc)(void*); // +0x0C: deallocation function pointer
};

extern void* allocateBuffer(size_t size); // FUN_009c8e50
extern void freeBuffer(void* ptr);        // thunk_FUN_009c8eb0

int* __thiscall EAStringBuffer::appendFromBuffer(EAStringBuffer* this, const void* sourceBase, int sourceOffset, size_t count) {
    int curLen = this->length;
    if (curLen != 0) {
        size_t newLen = curLen + count;
        if (newLen < this->capacity) {
            // fits within existing capacity
            memcpy(this->buffer + curLen, (const char*)sourceBase + sourceOffset, count);
        } else {
            // reallocate larger buffer
            void* newBuf = allocateBuffer(newLen + 1); // +1 for null terminator
            memcpy(newBuf, this->buffer, curLen);
            memcpy((char*)newBuf + curLen, (const char*)sourceBase + sourceOffset, count);
            if (this->buffer != nullptr) {
                this->deallocFunc(this->buffer);
            }
            this->buffer = (char*)newBuf;
            this->capacity = (int)newLen;
            this->deallocFunc = freeBuffer;
        }
        this->length += (int)count;
        this->buffer[this->length] = '\0';
        return this;
    } else {
        // empty buffer: delegate to initial allocation/assignment
        return FUN_004d3f10(sourceBase, sourceOffset, count);
    }
}