// FUNC_NAME: SomeManager::findFirstMatching
int * __thiscall SomeManager::findFirstMatching(int *pOutResult, int conditionParam)
{
    uint32_t count = *(uint32_t *)(this + 0x3C); // mCount at +0x3C
    pOutResult[0] = 0;
    pOutResult[1] = -1;

    if (count != 0) {
        uint32_t index = 0;
        // Iterate through items until a matching one is found
        while (true) {
            int result = FUN_00821be0(conditionParam); // isItemMatching
            if (result != 0) {
                pOutResult[0] = result;
                pOutResult[1] = index;
                break;
            }
            index++;
            if (index >= count) break;
        }
    }
    return pOutResult;
}