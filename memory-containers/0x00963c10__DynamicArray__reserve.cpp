// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int* thisPtr, uint newCapacity)
{
    // thisPtr[0] = data pointer (int*)
    // thisPtr[1] = count (size)
    // thisPtr[2] = capacity
    if ((uint)thisPtr[2] < newCapacity) {
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // allocate new buffer
        if (thisPtr[0] != 0) {
            uint i = 0;
            int* dest = newData;
            if (thisPtr[1] != 0) {
                do {
                    if (dest != (int*)0x0) {
                        *dest = *(int*)(thisPtr[0] + i * 4);
                    }
                    i++;
                    dest++;
                } while (i < (uint)thisPtr[1]);
            }
            FUN_009c8f10(thisPtr[0]); // free old buffer
        }
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
    return;
}