// FUNC_NAME: EAString::reserve
void EAString::reserve(int newSize) {
    if (mCapacity < newSize) {
        if (newSize >= 16) { // Note: 0x10 = 16, threshold for using heap
            // Allocate new buffer with room for null terminator
            char* newBuffer = (char*)DAT_0119caf0(newSize + 1, 0); // calloc? second param 0 means allocate, no flags
            // Copy existing content
            char* src = mpBuffer;
            char* end = src + mLength;
            char* dst = newBuffer;
            while (src != end) {
                *dst++ = *src++;
            }
            // Free old buffer if it's not the inline buffer
            if (mpBuffer != mInlineBuffer && mpBuffer != nullptr) {
                DAT_0119caf4(mpBuffer);
            }
            // Update members
            mCapacity = newSize;
            mpBuffer = newBuffer;
            // Null-terminate
            newBuffer[mLength] = '\0';
        } else {
            // If newSize < 16, just update capacity without reallocation
            mCapacity = newSize;
        }
    }
}