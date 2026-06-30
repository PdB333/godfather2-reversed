// FUNC_NAME: EARSString::assign
int* __thiscall EARSString::assign(EARSString* this, const void* src, uint length) {
    if (length != 0) {
        // Reallocate if capacity is insufficient
        if (this->mCapacity <= length) {
            // Free old buffer if any
            if (this->mBuffer != nullptr) {
                this->mDeallocator(this->mBuffer);
            }
            // Allocate new buffer (length + 1 for null terminator)
            char* newBuf = FUN_009c8e50(length + 1);
            this->mBuffer = newBuf;
            this->mCapacity = length;
            this->mDeallocator = thunk_FUN_009c8eb0; // custom deallocator
        }
        // Copy data
        _memcpy(this->mBuffer, src, length);
        // Null-terminate
        this->mBuffer[length] = '\0';
        this->mLength = length;
        return this;
    }
    // Empty string: just set length to 0 and null-terminate existing buffer
    this->mLength = 0;
    if (this->mBuffer != nullptr) {
        this->mBuffer[0] = '\0';
    }
    return this;
}