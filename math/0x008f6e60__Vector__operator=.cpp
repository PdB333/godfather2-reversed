// FUNC_NAME: Vector::operator=
// Reconstructed copy assignment for a dynamic array structure (data, size, capacity)
// Structure layout: +0x00 data pointer (int*), +0x04 size (int), +0x08 capacity (int)
// Called from FUN_008f70c0 (likely another container or utility)

int* __thiscall Vector::operator=(int* thisPtr, int* otherPtr)
{
    int newCapacity = otherPtr[2];           // other->capacity
    thisPtr[2] = newCapacity;                // this->capacity = other->capacity
    thisPtr[1] = otherPtr[1];                // this->size = other->size

    if (newCapacity == 0)
    {
        thisPtr[0] = 0;                      // this->data = nullptr
    }
    else
    {
        // Allocate new buffer of ints
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // likely operator new[] / malloc
        thisPtr[0] = (int)newData;           // store as raw pointer (should be int* but stored as int)

        // Copy elements from other's data array
        if (thisPtr[1] != 0)
        {
            uint i = 0;
            int* otherData = (int*)otherPtr[0];
            do {
                newData[i] = otherData[i];
                i++;
            } while (i < (uint)thisPtr[1]);  // copy up to size
        }
    }
    return thisPtr;
}