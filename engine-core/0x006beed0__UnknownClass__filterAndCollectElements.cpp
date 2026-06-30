// FUNC_NAME: UnknownClass::filterAndCollectElements
// Function at 0x006beed0: iterates over a source array, filters elements matching a comparison value, 
// appends them to a dynamic destination array, then sorts the destination.
// The dynamic array structure: [pointer to buffer, count, capacity]
// param_1 (this) is used in notifyAdded callback.
void __thiscall UnknownClass::filterAndCollectElements(void* thisPtr, int* sourceArray, int* destArray, int compareValue)
{
    int sourceCount = sourceArray[1]; // source array count at +0x04
    reallocateArray(sourceCount); // unknown reallocation function (possibly just a no-op or memory prefetch)
    for (uint i = 0; i < sourceCount; i++)
    {
        int element = *(int*)(sourceArray[0] + i * 4); // sourceArray[0] = pointer to elements
        int filterValue = getFilterValue(); // returns a value compared to compareValue
        if (filterValue == compareValue)
        {
            // Dynamic array growth logic
            int destCount = destArray[1]; // current count
            int destCapacity = destArray[2]; // capacity
            if (destCount == destCapacity)
            {
                if (destCapacity == 0)
                {
                    destCapacity = 1;
                }
                else
                {
                    destCapacity *= 2;
                }
                reallocateArray(destCapacity);
            }
            int* destBuffer = (int*)destArray[0]; // pointer to buffer
            destBuffer[destCount] = element;
            destArray[1] = destCount + 1; // update count
            notifyAdded(thisPtr); // callback after adding element
        }
    }
    if (destArray[1] > 1)
    {
        qsort((void*)destArray[0], destArray[1], 4, elementComparator);
    }
}