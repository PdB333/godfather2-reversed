// FUNC_NAME: GlobalManager::popFirstElement
void FUN_00435b20(void)
{
    int count;
    int *arrayPtr;
    int iVar1;

    // Global singleton pointer (likely EngineManager or similar)
    void *gManager = *((void **)0x0122350c);  // DAT_0122350c is a static variable containing pointer to manager

    if (gManager != 0 && *(int *)((int)gManager + 0x173c) != 0) {
        count = *(int *)((int)gManager + 0x173c);
        arrayPtr = *(int **)((int)gManager + 0x1738);   // +0x1738: pointer to array of pairs (2 ints each)

        if (count != 1) {
            // Move the last pair to the front, overwriting the first
            arrayPtr[0] = arrayPtr[count * 2 + -2];   // last element's first int
            arrayPtr[1] = arrayPtr[count * 2 + -1];   // last element's second int
        }
        // Decrement count (effectively removes the last element after moving it to front)
        *(int *)((int)gManager + 0x173c) = count - 1;
    }
    return;
}