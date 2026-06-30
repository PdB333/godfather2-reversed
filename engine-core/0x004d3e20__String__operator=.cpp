// FUNC_NAME: String::operator=
int* __thiscall String::operator=(int *this, int *other)
{
    char cChar;
    uint otherLen;
    int newBuffer;
    char *srcPtr;
    char *dstPtr;

    if (this != other) {
        otherLen = other[1];                                         // +0x04: mLength of other
        if (otherLen != 0) {
            if ((uint)this[2] <= otherLen) {                          // +0x08: mCapacity
                if (this[0] != 0) {                                   // +0x00: mBuffer
                    (*(void (__thiscall *)(int *))this[3])(this[0]);  // +0x0C: mDeleter (custom deallocator)
                }
                newBuffer = FUN_009c8e50(otherLen + 1);                // allocate new buffer (size = length+1 for null)
                this[0] = newBuffer;
                this[2] = otherLen;                                    // update capacity
                this[3] = (int)thunk_FUN_009c8eb0;                     // set deallocator function
            }
            srcPtr = (char *)other[0];
            dstPtr = (char *)this[0];
            do {
                cChar = *srcPtr;
                *dstPtr = cChar;
                srcPtr = srcPtr + 1;
                dstPtr = dstPtr + 1;
            } while (cChar != '\0');
            this[1] = otherLen;                                        // update length
            return this;
        }
        // other string is empty
        this[1] = 0;
        if (this[0] != 0) {
            *(char *)this[0] = '\0';                                   // null-terminate existing buffer
        }
    }
    return this;
}