// FUNC_NAME: DynamicUShortArray::resize

void __thiscall DynamicUShortArray::resize(unsigned int newSize, unsigned short fillValue)
{
    // param_1 = this
    int *thisPtr = reinterpret_cast<int*>(this);
    unsigned short *buffer = reinterpret_cast<unsigned short*>(thisPtr[0]);  // +0x00
    unsigned int currentSize = thisPtr[1];                                   // +0x04: number of ushorts currently stored
    unsigned int capacityBytes = thisPtr[2];                                 // +0x08: buffer capacity in bytes
    void (*deallocator)(void*) = reinterpret_cast<void (*)(void*)>(thisPtr[3]); // +0x0C: custom deallocator function

    unsigned int newSizeBytes = newSize * sizeof(unsigned short);

    if (newSizeBytes < capacityBytes) {
        // Case 1: Buffer is large enough, just fill new elements
        for (unsigned int i = currentSize; i < newSize; i++) {
            buffer[i] = fillValue;
        }
        // Set null terminator and update size only if shrinking or non‑zero fill
        if (newSize < currentSize || fillValue != 0) {
            buffer[newSize] = 0;               // ushort null terminator
            thisPtr[1] = newSize;               // update size
        }
    }
    else if (newSizeBytes > capacityBytes) {
        // Case 2: Need to reallocate a larger buffer
        // Round up size to next block (mask sign bit then +1)
        unsigned int alignedSize = ((newSize & 0x7FFFFFFF) + 1) * sizeof(unsigned short);
        unsigned short *newBuffer = reinterpret_cast<unsigned short*>(FUN_009c8e50(alignedSize));

        if (buffer != nullptr) {
            // Copy existing data
            memcpy(newBuffer, buffer, currentSize * sizeof(unsigned short));
            if (buffer != nullptr) {
                deallocator(buffer);             // free old buffer
            }
        }

        thisPtr[0] = reinterpret_cast<int>(newBuffer);
        thisPtr[3] = reinterpret_cast<int>(thunk_FUN_009c8eb0);  // set deallocator

        // Fill the new elements with fillValue
        memset(reinterpret_cast<char*>(newBuffer) + currentSize * sizeof(unsigned short), fillValue, (newSize - currentSize) * sizeof(unsigned short));

        if (fillValue != 0) {
            thisPtr[1] = newSize;
            newBuffer[newSize] = 0;              // null terminator
        }

        thisPtr[2] = newSizeBytes;               // update capacity in bytes
    }
    // Note: When newSizeBytes == capacityBytes, no action is taken (size remains unchanged)
}