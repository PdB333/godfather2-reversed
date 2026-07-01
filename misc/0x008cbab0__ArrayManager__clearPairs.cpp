// FUNC_NAME: ArrayManager::clearPairs
void __thiscall ArrayManager::clearPairs(undefined4 *this) {
    int count = *(int *)((char *)this + 0xFA0);  // +0xFA0: number of pairs in the array
    if (count != 0) {
        if (count == 1) {
            *(int *)((char *)this + 0xFA0) = 0;
            return;
        }
        int i = 0;
        undefined4 *pairPtr = this;
        do {
            *pairPtr = 0;        // clear first int of pair (offset 0)
            pairPtr[1] = 0;      // clear second int of pair (offset 4)
            i++;
            pairPtr += 2;
        } while (i < count - 1);
    }
    *(int *)((char *)this + 0xFA0) = 0;
}