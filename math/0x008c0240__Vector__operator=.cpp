// FUNC_NAME: Vector::operator=
int* __thiscall Vector::operator=(int* thisPtr, int* otherPtr)
{
    int* oldData;
    uint i;
    uint newCapacity;
    int* newData;

    // thisPtr: pointer to Vector structure: +0 = data, +4 = size, +8 = capacity
    // otherPtr: source vector structure
    if (thisPtr != otherPtr)
    {
        // If current capacity is less than needed size, reallocate
        if ((uint)thisPtr[2] < (uint)otherPtr[1])
        {
            // Free old data
            FUN_009c8f10(*thisPtr); // free(this->data)

            // Set new capacity to source size
            newCapacity = otherPtr[1];
            thisPtr[2] = newCapacity;

            // Allocate new buffer if capacity > 0, else set to null
            if (newCapacity == 0)
            {
                newData = (int*)0;
            }
            else
            {
                newData = (int*)FUN_009c8e80(newCapacity * 4); // malloc(size * sizeof(int))
            }
            *thisPtr = (int)newData; // this->data = newData
        }

        // Copy elements from source to destination
        i = 0;
        if (otherPtr[1] != 0)
        {
            do
            {
                // Copy each 4-byte element
                *(int*)(*thisPtr + i * 4) = *(int*)(*otherPtr + i * 4);
                i = i + 1;
            } while (i < (uint)otherPtr[1]);
        }

        // Update size
        thisPtr[1] = otherPtr[1];
    }

    return thisPtr;
}