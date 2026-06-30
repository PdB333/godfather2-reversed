// FUNC_NAME: initializeObjectPool
void initializeObjectPool(void)
{
    undefined4 *poolItem = &DAT_0119a9d0; // Global array of 16 pool items, each 0x1D0 bytes
    for (int i = 0; i < 0x10; i++)
    {
        constructPoolItem(poolItem); // Initialize one pool item
        poolItem += 0x74; // Advance to next item (0x74 * 4 = 0x1D0 bytes)
    }
    return;
}