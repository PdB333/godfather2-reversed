// FUNC_NAME: processQueuedEvents
void processQueuedEvents(void)
{
    char secondType;  // from global+0x565
    int *pEntry;
    int entryValue;

    secondType = *(char *)(g_GlobalStruct + 0x565);
    if (((*(char *)(g_GlobalStruct + 0x564) != 0x12) && (g_ArrayIndex1 != -1)) &&
       (g_FirstEventArray[g_ArrayIndex1] != 0)) {
        entryValue = 0;
        while ((g_ArrayIndex1 != -1) &&
              (pEntry = &g_FirstEventArray[g_ArrayIndex1], *pEntry != 0)) {
            entryValue = *pEntry;
            g_ArrayIndex1 = g_ArrayIndex1 - 1;
        }
        pEntry = (int *)getObjectVTable(*(char *)(g_GlobalStruct + 0x564));
        (*(code **)(*pEntry + 8))(entryValue);
    }
    if (((secondType != 0x12) && (g_ArrayIndex2 != -1)) &&
       (g_SecondEventArray[g_ArrayIndex2] != 0)) {
        entryValue = 0;
        while ((g_ArrayIndex2 != -1) &&
              (pEntry = &g_SecondEventArray[g_ArrayIndex2], *pEntry != 0)) {
            entryValue = *pEntry;
            g_ArrayIndex2 = g_ArrayIndex2 - 1;
        }
        pEntry = (int *)getObjectVTable(*(char *)(g_GlobalStruct + 0x565));
        (*(code **)(*pEntry + 8))(entryValue);
    }
    return;
}