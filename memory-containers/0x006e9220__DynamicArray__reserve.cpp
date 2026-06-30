// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(DynamicArray* this, uint newCapacity)
{
    // Check if we need to grow
    if (this->mCapacity < newCapacity)
    {
        // Get allocator instance (or use default)
        void* allocator = this->mAllocator;
        if (allocator == nullptr)
        {
            allocator = &gDefaultAllocator; // DAT_01218a14
        }

        // Allocate new memory block via allocator vtable
        AllocatorVTable* vtable = this->mAllocatorVTable;
        int* newData = (int*)vtable->allocate(newCapacity * sizeof(int), allocator);

        // Copy existing elements
        if (this->mData != nullptr)
        {
            uint i = 0;
            int* src = this->mData;
            int* dst = newData;
            if (this->mSize != 0)
            {
                do
                {
                    if (dst != nullptr)
                    {
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < (uint)this->mSize);
            }
        }

        // Free old memory
        if (this->mData != nullptr)
        {
            vtable->deallocate(this->mData, 0);
        }

        // Update pointers and capacity
        this->mData = newData;
        this->mCapacity = newCapacity;
    }
}