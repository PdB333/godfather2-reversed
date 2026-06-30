// FUN_004d8a60: EARSStringArray::operator=
// Function address: 0x004d8a60
// Deep copy assignment operator for an array of dynamically allocated, counted strings.
// Each element of the array is 0x10 bytes: [0] = data pointer, [4] = data size, [8] = capacity, [0xC] = deallocator function pointer.

int* __thiscall EARSStringArray::operator=(const EARSStringArray* other) {
    if (this == other) {
        return this;
    }

    // Destroy existing elements in reverse order
    int oldCount = this->count - 1;  // param_1[1] (offset 4)
    if (oldCount >= 0) {
        int elementIndex = oldCount;
        do {
            int* element = reinterpret_cast<int*>(this->array + elementIndex * 0x10);
            void* dataPtr = reinterpret_cast<void*>(element[0]);  // +0x00 data pointer
            if (dataPtr != nullptr) {
                // Call the deallocator function stored at +0x0C
                typedef void (*Deallocator)(void*);
                Deallocator dealloc = reinterpret_cast<Deallocator>(element[3]);  // +0x0C
                dealloc(dataPtr);
            }
            --elementIndex;
        } while (elementIndex >= 0);
    }

    // Resize the array if the other array has more elements than current capacity
    if (static_cast<unsigned int>(this->capacity) < static_cast<unsigned int>(other->count)) {
        // Free old array buffer
        earFree(this->array);  // FUN_009c8f10 (earFree?)
        this->capacity = other->count;
        if (this->capacity != 0) {
            this->array = reinterpret_cast<int*>(earAlloc(this->capacity * 0x10));  // FUN_009c8e80 (earAlloc?)
        } else {
            this->array = nullptr;
        }
    }

    // Copy elements from other array
    unsigned int numElements = static_cast<unsigned int>(other->count);
    for (unsigned int i = 0; i < numElements; ++i) {
        int* destElement = reinterpret_cast<int*>(this->array + i * 0x10);
        int* srcElement = reinterpret_cast<int*>(other->array + i * 0x10);
        int srcDataSize = srcElement[1];  // +0x04 data size
        if (srcDataSize == 0) {
            // Source is empty: clear destination
            destElement[0] = 0;  // data pointer
            destElement[2] = 0;  // capacity
            destElement[1] = 0;  // size
        } else {
            destElement[1] = srcDataSize;                     // copy size
            destElement[2] = srcDataSize;                     // set capacity equal to size
            void* newData = earAlloc(srcDataSize + 1);       // FUN_009c8e50 (earAlloc with +1 for null terminator)
            destElement[0] = reinterpret_cast<int>(newData);
            memcpy(newData, reinterpret_cast<void*>(srcElement[0]), srcDataSize);
            // Null-terminate string data (assuming string)
            *reinterpret_cast<char*>(static_cast<char*>(newData) + srcDataSize) = '\0';
            destElement[3] = reinterpret_cast<int>(earDeallocFunc);  // thunk_FUN_009c8eb0 (earFree or similar)
        }
    }

    this->count = other->count;
    return this;
}