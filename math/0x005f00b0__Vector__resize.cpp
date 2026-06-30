// FUNC_NAME: Vector::resize

void Vector::resize(uint newCapacity)
{
    // +0x00: int* mData
    // +0x04: uint mSize
    // +0x08: uint mCapacity
    if (mCapacity < newCapacity)
    {
        int* newData = (int*)Allocate(newCapacity * 4); // FUN_009c8e80
        if (mData != nullptr)
        {
            for (uint i = 0; i < mSize; i++)
            {
                if (newData != nullptr)
                {
                    newData[i] = mData[i];
                }
            }
            Deallocate(mData); // FUN_009c8f10
        }
        mData = newData;
        mCapacity = newCapacity;
    }
    // else: no shrink, capacity unchanged
}