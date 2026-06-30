// FUNC_NAME: ObjectContainer::remove
void __thiscall ObjectContainer::remove(uint param_1, int element) // param_1 = this, param_2 = element to remove (pointer or ID)
{
    // First container: 4-byte elements, pointer at +0x5C, count at +0x60
    uint count1 = *(uint *)(param_1 + 0x60);
    if (count1 != 0) {
        int *array1 = *(int **)(param_1 + 0x5C);
        for (uint i = 0; i < count1; i++) {
            if (array1[i] == element) {
                // Found in first container; remove by swapping with last element
                if (i != count1 - 1) {
                    // Copy last element to index i
                    *(int *)(*(int *)(param_1 + 0x5C) + i * 4) = *(int *)(*(int *)(param_1 + 0x5C) + (count1 - 1) * 4);
                }
                *(uint *)(param_1 + 0x60) = count1 - 1;
                return;
            }
        }
    }

    // Second container: 8-byte elements, pointer at +0x68, count at +0x6C
    int index2 = findInSecondContainer(param_2); // FUN_006bcb20 - searches for element in second container
    if (index2 >= 0) {
        int count2 = *(int *)(param_1 + 0x6C);
        if (index2 != count2 - 1) {
            int *array2 = *(int **)(param_1 + 0x68);
            // Copy last 8-byte element to index2
            *(int *)(array2 + index2 * 2) = *(int *)(array2 + (count2 - 1) * 2);
            *(int *)(array2 + index2 * 2 + 1) = *(int *)(array2 + (count2 - 1) * 2 + 1);
        }
        *(int *)(param_1 + 0x6C) = count2 - 1;
    }
}