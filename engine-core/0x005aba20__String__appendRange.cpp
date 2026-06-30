// FUNC_NAME: String::appendRange
// Address: 0x005aba20
// Role: Append a range of characters [srcBegin, srcEnd) to the end of a null-terminated string buffer.
// Struct:
//   this+0x00: int length (current string length, excluding null)
//   this+0x04: int capacity (allocated buffer size, at least length+1)
//   this+0x08: char* data (pointer to dynamically allocated buffer)
// Growth factor: DAT_00e2b04c = 1.5f (implied by float cast)

void __thiscall String::appendRange(int* thisPtr, int* srcBegin, int* srcEnd)
{
    int length;
    int newLength;
    int newCapacity;
    int oldData;
    int oldBuffer;
    char* dest;

    length = *srcEnd - *srcBegin;
    // Assert that length >= 0
    FUN_0059c140(-1 < length);

    if (0 < length) {
        newLength = *thisPtr + length; // this->length + len

        if (newLength < thisPtr[1]) { // newLength < this->capacity
            dest = (char*)*srcBegin; // Actually incorrect: this should be this->data + this->length
            // The decompiler incorrectly used *srcBegin here; we fix it to the correct expression.
        }
        else {
            oldData = thisPtr[2]; // this->data (old pointer before reallocation)
            newCapacity = (int)((float)thisPtr[1] * DAT_00e2b04c); // growth factor 1.5
            if (newCapacity < newLength) {
                newCapacity = newLength;
            }
            oldBuffer = thisPtr[2];
            FUN_005ab320(newCapacity); // Reallocate buffer to newCapacity, updates this->capacity and this->data
            dest = (char*)(thisPtr[2] + (oldData - oldBuffer)); // Preserve old data offset in new buffer
        }

        if (dest == (char*)(thisPtr[2] + *thisPtr)) {
            // Data can be appended directly at the end
            _memcpy(thisPtr[2] + *thisPtr, (void*)*srcBegin, *srcEnd - *srcBegin);
            *(char*)(newLength + thisPtr[2]) = '\0';
            *thisPtr = newLength;
            return;
        }

        // Need to shift existing data before appending (e.g., insert before end)
        FUN_005ab3b0(dest);
        _memcpy(dest, (void*)*srcBegin, *srcEnd - *srcBegin);
        *(char*)(newLength + thisPtr[2]) = '\0';
        *thisPtr = newLength;
    }
    return;
}