// FUNC_NAME: SomeClass::findEntryIndex
int __thiscall SomeClass::findEntryIndex(int param_1, int param_2) {
    int index = -1;
    int result = index;
    if (param_2 != 0) {
        // Array of pairs at +0x68, count at +0x6c (number of pairs)
        int* pArray = *(int**)(param_1 + 0x68);
        int* pEnd = pArray + (*(int*)(param_1 + 0x6c) * 2); // Each pair is two ints
        int i = 0;
        if (pArray != pEnd) {
            do {
                result = i;
                if (*pArray == param_2) {
                    break; // Found, result is index
                }
                pArray += 2;
                i = result + 1;
            } while (pArray != pEnd);
            if (pArray == pEnd) {
                // Not found
                return -1;
            }
        }
    }
    return result;
}