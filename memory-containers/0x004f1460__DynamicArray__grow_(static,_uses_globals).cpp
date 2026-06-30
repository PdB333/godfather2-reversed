// FUNC_NAME: DynamicArray::grow (static, uses globals)
// Address: 0x004f1460
// Resizes a global dynamic array of 8-byte elements.
// Globals:
// s_pArray (DAT_01218f28) - pointer to array of 8-byte elements
// s_capacity (DAT_01218f30) - current capacity (number of elements)
// s_count (DAT_01218f2c) - number of elements currently in use
void DynamicArray::grow(unsigned int newCapacity)
{
    void* newArray;
    unsigned int cap = s_capacity;
    unsigned int i;

    if (newCapacity > cap)
    {
        // Allocate new array with element size 8
        newArray = FUN_009c8e80(newCapacity * 8);

        if (s_pArray != nullptr)
        {
            // Copy existing elements (each element is 8 bytes: two DWORDs)
            i = 0;
            do {
                if (newArray != nullptr)
                {
                    ((unsigned int*)newArray)[i * 2]     = ((unsigned int*)s_pArray)[i * 2];
                    ((unsigned int*)newArray)[i * 2 + 1] = ((unsigned int*)s_pArray)[i * 2 + 1];
                }
                i++;
            } while (i < s_count);

            // Free old array
            FUN_009c8f10(s_pArray);
        }

        // Update capacity
        cap = newCapacity;
    }

    // Update globals
    s_capacity = cap;
    s_pArray = newArray;
}