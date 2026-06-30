// FUNC_NAME: Vector::insert
struct Vector {
    // +0x00: mpBegin
    // +0x04: mpEnd
    // +0x08: mpCapacityEnd
    void* mpBegin;
    void* mpEnd;
    void* mpCapacityEnd;

    // Element size = 0x504 bytes = 0x141 * 4 uint32s
    static const int kElementSize = 0x504;
    static const int kElementSizeInUint32 = 0x141;

    // Helper functions (extern from other compilation units)
    extern void internalShift(void* dest, void* src, void* end);     // FUN_00699d80
    extern void* allocateMemory(size_t size);                         // FUN_0068ab90
    extern void constructionRange(void* block, void* first, void* last, void* newBlock); // FUN_00698d60
    extern void deallocateMemory(void* ptr);                          // FUN_009c8f10

    void insert(void* position, void* value) {
        // Cast to uint32* for pointer arithmetic
        uint32_t* pPosition = (uint32_t*)position;
        uint32_t* pValue = (uint32_t*)value;
        uint32_t* pEnd = (uint32_t*)mpEnd;
        uint32_t* pCapEnd = (uint32_t*)mpCapacityEnd;

        if (pEnd != pCapEnd) {
            // Space available, insert in-place
            // Adjust value pointer if it lies in the shifted range
            if ((pPosition <= pValue) && (pValue < pEnd)) {
                pValue += kElementSizeInUint32;
            }

            // If the vector is non-empty, duplicate the last element to the end
            if (pEnd != nullptr) {
                uint32_t* pSrc = pEnd - kElementSizeInUint32;
                for (int i = 0; i < kElementSizeInUint32; ++i) {
                    *pEnd = *pSrc;
                    ++pSrc;
                    ++pEnd;
                }
            }

            // Shift elements from position to old end right by one slot
            internalShift(pPosition, ((uint32_t*)mpEnd) - kElementSizeInUint32, mpEnd);

            // Copy the new value into the vacated position
            for (int i = 0; i < kElementSizeInUint32; ++i) {
                *pPosition = *pValue;
                ++pValue;
                ++pPosition;
            }

            // Update the end pointer
            mpEnd = (char*)mpEnd + kElementSize;
        } else {
            // Must reallocate: double capacity
            int numElements = ((char*)pEnd - (char*)mpBegin) / kElementSize;
            int newCapacity = (numElements == 0) ? 1 : numElements * 2;
            // Ensure new capacity is not zero
            if (newCapacity == 0) {
                newCapacity = 1;
            }

            size_t newSize = newCapacity * kElementSize;
            void* newBlock = allocateMemory(newSize);

            // Construct the new element at the beginning of newBlock
            constructionRange(&newBlock, mpBegin, (void*)pPosition, newBlock);

            // Copy the new value to the new block's start
            uint32_t* pNewStart = (uint32_t*)newBlock;
            for (int i = 0; i < kElementSizeInUint32; ++i) {
                *pNewStart = *pValue;
                ++pValue;
                ++pNewStart;
            }

            // Construct remaining elements after the inserted one
            constructionRange(&newBlock, (void*)((uint32_t*)pPosition + kElementSizeInUint32), (void*)pEnd,
                            (void*)((uint32_t*)newBlock + kElementSizeInUint32));

            // Free old memory
            if (mpBegin != nullptr) {
                deallocateMemory(mpBegin);
            }

            // Update pointers
            mpCapacityEnd = (char*)newBlock + newSize;
            mpBegin = newBlock;
            mpEnd = (char*)newBlock + (numElements + 1) * kElementSize;
        }
    }
};