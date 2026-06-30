// FUNC_NAME: DynamicArray::reserve
// Function at 0x0048e040: Resize internal array to new capacity (reserve more slots)
// This is a typical reallocation for a dynamic array/vector used in EA EARS engine.
// The array structure (this pointer via ECX) has the following layout:
//   +0x00 : int*    mData       - pointer to allocated element array
//   +0x04 : uint32  mSize       - number of elements currently used
//   +0x08 : uint32  mCapacity   - current capacity (max elements before realloc)
//   +0x0C : void*   mAllocatorPtr - optional allocator pointer (if null, use global default)
//   +0x10 : void*   mAllocatorObj - allocator object with vtable (for allocate/deallocate)

void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // Only reallocate if new capacity exceeds the current capacity
    if (newCapacity > this->mCapacity)
    {
        // Get the allocator to use (default to global allocator if no custom one)
        void* allocator = this->mAllocatorPtr;
        if (allocator == nullptr)
        {
            allocator = &DAT_01218a14; // Global default allocator (0x01218a14)
        }

        // Call allocate function from the allocator object's vtable (index 0)
        // Allocation size = newCapacity * sizeof(int) (4 bytes per element)
        int* newData = reinterpret_cast<int*>(
            (*(code **)*reinterpret_cast<void***>(this->mAllocatorObj)) // vtable[0]
            (newCapacity * 4, allocator)
        );

        // Copy existing elements from old data to new block, if any
        if (this->mData != nullptr && this->mSize > 0)
        {
            for (uint i = 0; i < this->mSize; i++)
            {
                newData[i] = this->mData[i];
            }
        }

        // Deallocate the old data block using allocator's deallocate (vtable index 1)
        if (this->mData != nullptr)
        {
            (*(code **)(*reinterpret_cast<void***>(this->mAllocatorObj) + 4)) // vtable[1]
                (this->mData, 0); // second argument likely flags (0)
        }

        // Update members to the new block and capacity
        this->mData = newData;
        this->mCapacity = newCapacity;
    }
}