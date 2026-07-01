//FUNC_NAME: KeyedArray::findIndex
uint __thiscall KeyedArray::findIndex(int *key)
{
    uint count = *(uint *)(this + 0xc); // +0xc: number of elements
    uint notFound = 0xffffffff;
    uint index = notFound;

    if (count != 0) {
        int *elementPtr = (int *)(*(int *)(this + 0x8) + 0x20); // +0x8: pointer to buffer, skip 0x20 header
        index = 0;
        while (elementPtr[-2] != key[0] || elementPtr[-1] != key[1] || elementPtr[0] != key[2] || elementPtr[1] != key[3]) {
            index++;
            elementPtr += 0xb; // each element is 0x2C bytes (11 ints)
            if (count <= index) {
                return notFound;
            }
        }
    }
    return index;
}