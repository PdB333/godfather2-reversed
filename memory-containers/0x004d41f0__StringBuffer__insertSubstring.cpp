// FUNC_NAME: StringBuffer::insertSubstring
// Function at 0x004d41f0: Insert data into a dynamic string/buffer with reallocation if needed.
// The string struct layout (assuming 32-bit):
//   +0x00: char* mData
//   +0x04: uint32_t mSize (current string length, not including null terminator)
//   +0x08: uint32_t mCapacity (allocated size, maybe includes space for null)
//   +0x0C: void (*mDeallocator)(void*) (free function pointer)

int* __thiscall StringBuffer::insert(uint pos, const void* srcBase, uint srcOffset, size_t count)
{
    uint oldSize;
    char temp;
    char* newBuffer;
    char* srcPtr;
    char* dstPtr;
    int* piVar5;

    if (count != 0) {
        oldSize = this->mSize;  // param_1[1]
        if (oldSize == 0) {
            // Buffer is empty: delegate to another function that initializes from substring?
            piVar5 = (int*)FUN_004d3f10(srcBase, srcOffset, count);
            return piVar5;
        }
        if (oldSize <= pos) {
            // Position beyond end: delegate to append function
            piVar5 = (int*)FUN_004d43f0(srcBase, srcOffset, count);
            return piVar5;
        }

        uint newSize = oldSize + count;  // uVar1
        if (this->mCapacity <= newSize) {
            // Need to grow: allocate new buffer, copy data, insert, copy tail, free old
            newBuffer = (char*)FUN_009c8e50(newSize + 1);  // allocate with space for null terminator
            memcpy(newBuffer, this->mData, pos);                     // copy first part
            memcpy(newBuffer + pos, (const char*)srcBase + srcOffset, count);  // insert new data
            // Copy the remainder (including null terminator) from old buffer after insert point
            srcPtr = this->mData + pos;      // start of old tail (including the character that was at pos)
            dstPtr = newBuffer + pos + count; // position where tail goes in new buffer
            do {
                temp = *srcPtr;
                *dstPtr = temp;
                srcPtr++;
                dstPtr++;
            } while (temp != '\0');  // copies until null terminator

            if (this->mData != 0) {
                this->mDeallocator(this->mData);  // free old buffer
            }
            this->mSize = oldSize + count;      // update length
            this->mCapacity = newSize;           // new capacity
            this->mData = newBuffer;
            this->mDeallocator = thunk_FUN_009c8eb0; // new deallocator function
            return this;
        } else {
            // Capacity sufficient: move tail to make room, then copy insertion
            memmove(this->mData + pos + count, this->mData + pos, oldSize - pos);
            memcpy(this->mData + pos, (const char*)srcBase + srcOffset, count);
            this->mSize = oldSize + count;
            // Ensure null terminator at end
            *(this->mData + this->mSize) = '\0';
            return this;
        }
    }
    return this;
}