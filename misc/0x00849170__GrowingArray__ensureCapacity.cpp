// FUNC_NAME: GrowingArray::ensureCapacity
void __thiscall GrowingArray::ensureCapacity(int* this, uint newCapacity)
{
    int* dataPtr;       // pointer to element array
    uint oldSize;       // number of elements currently used
    uint oldCapacity;   // current allocated capacity

    oldCapacity = this[2];
    if (oldCapacity < newCapacity)
    {
        // Allocate new buffer: newCapacity elements, each 4 bytes
        dataPtr = (int*)allocateMemory(newCapacity * 4);
        oldSize = this[1];
        if (this[0] != 0 && oldSize != 0)
        {
            // Copy existing elements into new buffer
            for (uint i = 0; i < oldSize; i++)
            {
                dataPtr[i] = *(int*)(this[0] + i * 4);
            }
        }
        // Free old buffer
        freeMemory((void*)this[0]);
        // Update this
        this[0] = (int)dataPtr;
        this[2] = newCapacity;
    }
}