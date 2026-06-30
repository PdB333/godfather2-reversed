// FUNC_NAME: FixedStringArray::operator=
// Address: 0x004d8a60 - Copy assignment operator for a fixed-size array of strings (each string is allocated separately).
// Each element is a 16-byte struct: [0] char* data, [4] int length, [8] int capacity, [12] void (*deallocator)(char*)
// The container itself is: [0] Element* elements, [1] int count, [2] int capacity (number of allocated slots)
// Internal allocators: allocateBuffer (new[] of bytes), freeBuffer (delete[]), allocateString (malloc), deallocateString (free)
// This function performs a deep copy, destroys existing elements, and allocates a new buffer if needed.

__thiscall FixedStringArray* FixedStringArray::operator=(FixedStringArray* this, const FixedStringArray* other)
{
    int i;
    void* dstStr;
    int otherCount;
    int* destElem;
    int srcBase;
    int srcStr;
    int newSize;

    if (this != other) {
        // Destroy existing elements in reverse order
        otherCount = this->count - 1;  // Actually this->count is at +4
        if (otherCount >= 0) {
            int offset = otherCount * 0x10; // each element is 16 bytes
            do {
                void* dataPtr = *(void**)(this->elements + offset); // element[0].data
                if (dataPtr != 0) {
                    void (*destructor)(void*) = *(void (**)(void*))(this->elements + offset + 0xc);
                    destructor(dataPtr);
                }
                otherCount--;
                offset -= 0x10;
            } while (otherCount >= 0);
        }

        // If current capacity is insufficient, reallocate the element array
        if ((uint)this->capacity < (uint)other->count) {
            freeBuffer(this->elements);
            this->capacity = other->count;
            newSize = other->count << 4;
            if (newSize == 0) {
                this->elements = 0;
            } else {
                this->elements = (Element*)allocateBuffer(newSize);
            }
        }

        // Copy elements from other
        uint idx = 0;
        if (other->count != 0) {
            int offset = 0;
            do {
                destElem = (int*)(this->elements + offset);
                if (destElem != 0) {
                    srcBase = (int)other->elements;
                    srcStr = *(int*)(srcBase + 4 + offset); // other->elements[offset/16].data length? Actually offset+4 is the length field
                    if (srcStr == 0) {
                        destElem[0] = 0; // data
                        destElem[2] = 0; // capacity
                        destElem[1] = 0; // length
                    } else {
                        destElem[1] = srcStr; // length
                        destElem[2] = srcStr; // capacity (same as length)
                        dstStr = (void*)allocateString(srcStr + 1); // +1 for null
                        destElem[0] = (int)dstStr; // data
                        memcpy(dstStr, *(void**)(srcBase + offset), destElem[1]); // copy source data (source string pointer is at srcBase+offset)
                        *(char*)(destElem[0] + destElem[1]) = 0; // null terminate
                        destElem[3] = (int)deallocateString; // default deallocator
                    }
                }
                idx++;
                offset += 0x10;
            } while (idx < (uint)other->count);
        }

        this->count = other->count;
    }

    return this;
}