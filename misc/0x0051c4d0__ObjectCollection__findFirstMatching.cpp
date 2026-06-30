// FUNC_NAME: ObjectCollection::findFirstMatching
int ObjectCollection::findFirstMatching(int param_1, int queryParam)
{
    int count = *(short *)(param_1 + 0x80);
    int i = 0;
    if (0 < count) {
        int *entryPtr = (int *)(param_1 + 0xf4);
        do {
            if (*entryPtr != 0) {
                int obj = *entryPtr;
                int vtable = *(int *)obj;
                int (*vfunc)(int) = *(int (**)(int))(vtable + 0x38);
                int result = vfunc(queryParam);
                if (result != 0) {
                    return result;
                }
            }
            i = i + 1;
            entryPtr = entryPtr + 5; // +20 bytes per entry
        } while (i < count);
    }
    return 0;
}