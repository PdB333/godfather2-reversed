// FUNC_NAME: EntityHandleMap::getHandle
int __fastcall EntityHandleMap::getHandle(int thisPtr, int entityPtr)
{
    int *node;
    int hash;

    if (entityPtr == 0) {
        return -1;
    }
    // +0x1fc: bool m_useDirectHandle
    // +0x30: entity flags, bit 1 = m_hasDirectHandle
    if (*(int *)(thisPtr + 0x1fc) == 0 || (*(uint *)(entityPtr + 0x30) >> 1 & 1) != 0) {
        // +0x18: cached handle in the entity itself
        return *(int *)(entityPtr + 0x18);
    }
    // Hash based on entity pointer divided by object alignment (0x34 = 52 bytes)
    hash = (entityPtr / 0x34) & 0x3ff;
    // +0x218: pointer to hash table array (size 0x400)
    for (node = *(int **)(*(int *)(thisPtr + 0x218) + hash * 4);
         node != (int *)0x0;
         node = (int *)node[6])   // +0x18: next pointer
    {
        if (node[0] == entityPtr && ((*(byte *)(node + 8) & 0x3c) == 0)) {
            // +0x28: stored handle value
            return node[10];
        }
    }
    return -1;
}