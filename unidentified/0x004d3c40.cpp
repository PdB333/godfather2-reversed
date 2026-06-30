// FUN_004d3c40: StringBuffer::initFromData

void __thiscall StringBuffer::initFromData(void *this, const void *sourceData, int dataSize)
{
    char *buffer;

    if (dataSize != 0) {
        // Set initial length and capacity to the data size
        *(int *)((char *)this + 4) = dataSize;   // +0x04: mCapacity
        *(int *)((char *)this + 8) = dataSize;   // +0x08: mLength

        // Allocate one extra byte for null terminator
        buffer = (char *)FUN_009c8e50(dataSize + 1);
        *(char **)this = buffer;                 // +0x00: mData

        // Copy the source data
        memcpy(buffer, sourceData, dataSize);

        // Null-terminate the string
        buffer[dataSize] = '\0';

        // Set the destructor/deallocation function pointer
        *(void (**)(void))(this + 12) = thunk_FUN_009c8eb0; // +0x0C: mDeleter
        return;
    }

    // Empty string: set all fields to zero
    *(char **)this = 0;
    *(int *)((char *)this + 8) = 0;
    *(int *)((char *)this + 4) = 0;
}