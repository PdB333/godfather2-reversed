// FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(int this, int object)
{
    uint count;
    int *arrayPtr;
    uint i;
    int *arrayBase;
    uint foundIndex;

    // Select the appropriate array based on object type (offset +0x58)
    switch (*(int *)(object + 0x58)) {
    default:
        arrayPtr = (int *)(this + 4);      // +0x04: array1 (pointer + count)
        break;
    case 2:
        arrayPtr = (int *)(this + 0x10);   // +0x10: array2
        break;
    case 3:
        arrayPtr = (int *)(this + 0x1c);   // +0x1c: array3
        break;
    case 4:
        arrayPtr = (int *)(this + 0x28);   // +0x28: array4
    }

    count = arrayPtr[1];                   // +0x04 from arrayPtr: element count
    foundIndex = 0;
    i = 0;
    uint lastIndex = 0xffffffff;           // sentinel for "not found"

    if (count != 0) {
        arrayBase = (int *)*arrayPtr;      // +0x00: pointer to array data
        do {
            lastIndex = i;
            if (*arrayBase == object) break;
            i = i + 1;
            arrayBase = arrayBase + 1;
            lastIndex = 0xffffffff;
        } while (i < count);
    }

    // If found and not the last element, replace with last element
    if (lastIndex != count - 1) {
        *(int *)(*arrayPtr + lastIndex * 4) = *(int *)(*arrayPtr + (count - 1) * 4);
    }

    // Decrement count
    arrayPtr[1] = arrayPtr[1] - 1;
    return;
}