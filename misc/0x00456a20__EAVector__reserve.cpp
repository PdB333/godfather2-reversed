// FUNC_NAME: EAVector::reserve
void __thiscall EAVector::reserve(uint newCapacity)
{
    // Structure assumed:
    // +0x00: int* mData
    // +0x04: uint mCount
    // +0x08: uint mCapacity
    int* mData = *(int**)this;
    uint mCount = *(uint*)((char*)this + 4);
    uint mCapacity = *(uint*)((char*)this + 8);

    if (newCapacity > mCapacity)
    {
        // Allocate new buffer (4 bytes per element)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);  // allocateMemory
        if (newData != nullptr)
        {
            // Copy existing elements
            for (uint i = 0; i < mCount; i++)
            {
                newData[i] = mData[i];
            }
        }
        // Free old buffer (if any)
        if (mData != nullptr)
        {
            FUN_009c8f10(mData);  // freeMemory
        }
        // Update pointers and capacity
        *(int**)this = newData;
        *(uint*)((char*)this + 8) = newCapacity;
    }
}