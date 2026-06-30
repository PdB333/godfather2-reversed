// FUNC_NAME: executeGlobalDelegate
void executeGlobalDelegate(void)
{
    // Calls the global data processing function with the global registry pointer (0x01223404)
    processGlobalData(g_globalDataRegistry);
}