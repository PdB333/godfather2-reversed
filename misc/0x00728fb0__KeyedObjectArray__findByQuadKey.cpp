// FUNC_NAME: KeyedObjectArray::findByQuadKey
int __thiscall KeyedObjectArray::findByQuadKey(int thisPtr, int *quadKey) {
    int count = *(int *)(thisPtr + 0x20);
    int foundObj = 0;
    if (count != 0) {
        int **arrayPtr = *(int ***)(thisPtr + 0x1c); // pointer to array of object pointers
        do {
            int *obj = *arrayPtr;
            // Compare 4 ints at offsets 0x20, 0x24, 0x28, 0x2c against the quad key
            if (obj[0x20 / 4] == quadKey[0] &&
                obj[0x24 / 4] == quadKey[1] &&
                obj[0x28 / 4] == quadKey[2] &&
                obj[0x2c / 4] == quadKey[3]) {
                foundObj = (int)obj;
            }
            arrayPtr++;
            count--;
        } while (count != 0);
    }
    return foundObj;
}