// FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(int thisPtr, int objectId) {
    // First array: local objects? Count at +0xa8, pointer at +0xa0
    short count1 = *(short *)(thisPtr + 0xa8);
    int index = 0;
    if (count1 > 0) {
        int *arr1 = *(int **)(thisPtr + 0xa0);
        while (index < count1) {
            if (arr1[index * 8] == objectId) { // int* stepping by 8 (0x20 bytes)
                if ((count1 > 1) && (index != count1 - 1)) {
                    // Swap last element into deleted slot
                    int base = *(int *)(thisPtr + 0xa0);
                    unsigned long long *dest = (unsigned long long *)(index * 0x20 + base);
                    unsigned long long *src = (unsigned long long *)((count1 - 1) * 0x20 + base);
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                }
                *(short *)(thisPtr + 0xa8) = count1 - 1;
                FUN_00572a00(*(int *)(thisPtr + 0xa0), (int)*(short *)(thisPtr + 0xa8));
                return;
            }
            index++;
            arr1 += 8; // each element is 0x20 bytes, so int* increments by 8
        }
    }

    // Second array: remote objects? Count at +0xaa, pointer at +0xa4
    short count2 = *(short *)(thisPtr + 0xaa);
    index = 0;
    if (count2 > 0) {
        int *arr2 = *(int **)(thisPtr + 0xa4);
        int *current = arr2;
        while (current[0] != objectId) {
            index++;
            current += 8;
            if (index >= *(short *)(thisPtr + 0xaa)) {
                return; // not found
            }
        }
        // Remove by swapping with last element if not last
        if ((*(short *)(thisPtr + 0xaa) > 1) && (index != count2 - 1)) {
            unsigned long long *dest = (unsigned long long *)(arr2 + index * 8);
            unsigned long long *src = (unsigned long long *)(arr2 + (count2 - 1) * 8);
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
        }
        *(short *)(thisPtr + 0xaa) = count2 - 1;
        FUN_00572a00(*(int *)(thisPtr + 0xa4), (int)*(short *)(thisPtr + 0xaa));
    }
}