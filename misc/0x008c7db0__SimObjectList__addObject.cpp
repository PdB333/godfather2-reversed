// FUNC_NAME: SimObjectList::addObject
void __thiscall SimObjectList::addObject(int thisPtr, int objPtr)
{
    int *arrayData;
    int currentSize;
    int capacity;

    // First array: all objects
    currentSize = *(int *)(thisPtr + 0x28);
    capacity = *(int *)(thisPtr + 0x2c);
    if (currentSize == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        resizeArray(capacity); // Reallocate first array to new capacity
    }
    arrayData = (int *)(*(int *)(thisPtr + 0x24) + currentSize * 4);
    *(int *)(thisPtr + 0x28) = currentSize + 1;
    if (arrayData != (int *)0x0) {
        *arrayData = objPtr;
    }

    // Second array: only if object has flag at +0x1d0
    if (*(int *)(objPtr + 0x1d0) != 0) {
        currentSize = *(int *)(thisPtr + 0x34);
        capacity = *(int *)(thisPtr + 0x38);
        if (currentSize == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity = capacity * 2;
            }
            resizeArray(capacity); // Reallocate second array to new capacity
        }
        arrayData = (int *)(*(int *)(thisPtr + 0x30) + currentSize * 4);
        *(int *)(thisPtr + 0x34) = currentSize + 1;
        if (arrayData != (int *)0x0) {
            *arrayData = objPtr;
        }
    }
}