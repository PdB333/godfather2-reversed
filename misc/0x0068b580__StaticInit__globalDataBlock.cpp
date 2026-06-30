// FUNC_NAME: StaticInit::globalDataBlock

void StaticInit::globalDataBlock(void)
{
    // Call the initialization function for the global data block at 0x012067d4
    initGlobalData(&g_globalDataBlock);
}