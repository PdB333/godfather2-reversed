// FUNC_NAME: findIndexByValue
uint __thiscall findIndexByValue(void* this, int* valuePtr)
{
    uint count = *(uint*)((int)this + 0x10); // +0x10: number of elements in the array
    uint index = 0xFFFFFFFF; // not found
    if (count != 0) {
        int targetValue = *valuePtr;
        index = 0;
        while (*(int*)((int)this + index * 4) != targetValue) {
            index++;
            if (index >= count) {
                return 0xFFFFFFFF; // not found, return -1
            }
        }
    }
    return index; // found at this index
}