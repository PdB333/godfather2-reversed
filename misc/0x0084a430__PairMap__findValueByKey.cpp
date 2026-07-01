// FUNC_NAME: PairMap::findValueByKey
int __thiscall PairMap::findValueByKey(int* thisPtr) {
    // thisPtr layout:
    // +0x00: pointer to some object (struct with field at +0x04 used as key base)
    // +0x04: ?
    // +0x08: ?
    // +0x0C: ?
    // +0x10: pointer to array of {int value, int key} pairs
    // +0x14: number of pairs in array

    unsigned int pairCount = thisPtr[5]; // offset 0x14
    int result = 0;
    if (pairCount != 0) {
        int* keyBase = (int*)*thisPtr; // dereference pointer at offset 0x00
        int targetKey = keyBase[1] - 1; // key = (keyBase->field_at_+0x04) - 1
        int* pairArray = (int*)thisPtr[4]; // offset 0x10
        unsigned int i = 0;
        while (true) {
            // Each pair: [0]=value, [1]=key
            if (pairArray[1] == targetKey) {
                result = pairArray[0];
                break;
            }
            i++;
            if (i >= pairCount)
                break;
            pairArray += 2; // advance to next pair
        }
    }
    return result;
}