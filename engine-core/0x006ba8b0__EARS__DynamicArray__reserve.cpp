// FUNC_NAME: EARS::DynamicArray::reserve

void DynamicArray::reserve(uint newCapacity)
{
    // Only reallocate if current capacity is insufficient
    if (mCapacity < newCapacity)
    {
        int* newData = (int*)operator new[](newCapacity * sizeof(int));

        // Copy existing elements if any data exists
        if (mData != nullptr)
        {
            uint i = 0;
            int* dst = newData;   // destination pointer
            while (i < mSize)
            {
                *dst = mData[i];
                i++;
                dst++;
            }
            // Free old memory
            operator delete[](mData);
        }

        // Update internal state
        mData = newData;
        mCapacity = newCapacity;
    }
}