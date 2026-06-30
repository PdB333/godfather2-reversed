// FUNC_NAME: EARSStringBuffer::setFill
void __thiscall EARSStringBuffer::setFill(unsigned int newLen, char fillChar) {
    // this structure: [0] mBuffer (char*), [4] mLength (uint), [8] mCapacity (uint), [12] mDealloc (function pointer, free)
    // Allocator used: FUN_009c8e50 (likely operator new or custom), deallocator: thunk_FUN_009c8eb0 (custom delete)

    if (newLen < this->mCapacity) {
        // Case 1: new length fits within current capacity
        // Fill from current length up to newLen with fillChar
        for (uint i = this->mLength; i < newLen; i++) {
            *(this->mBuffer + i) = fillChar;
        }
        // Null-terminate only if we are shrinking (newLen < old len) or fillChar is non-zero
        if ((newLen < this->mLength) || (fillChar != '\0')) {
            *(this->mBuffer + newLen) = '\0';
            this->mLength = newLen;
        }
        // If fillChar is '\0' and newLen >= oldLen, we just leave buffer as is (no null, length unchanged)
        return;
    }

    if (this->mCapacity < newLen) {
        // Case 2: need to grow capacity
        char* newBuf = (char*)FUN_009c8e50(newLen + 1); // allocate new buffer (extra for null)
        if (this->mBuffer != nullptr) {
            // Copy old contents
            _memcpy(newBuf, this->mBuffer, this->mLength);
            // Free old buffer using custom deallocator
            if (this->mBuffer != 0) {
                (*(void (*)(void*))this->mDealloc)(this->mBuffer);
            }
        }
        this->mBuffer = newBuf;
        this->mDealloc = (int)thunk_FUN_009c8eb0; // assign deallocator

        // Fill the gap (old length to newLen) with fillChar
        _memset(newBuf + this->mLength, (int)fillChar, newLen - this->mLength);

        if (fillChar != '\0') {
            // Only update length and null-terminate if fillChar is non-zero
            this->mLength = newLen;
            *(this->mBuffer + newLen) = '\0';
        }
        this->mCapacity = newLen;
    }
    // If newLen == capacity, do nothing (already fits)
}