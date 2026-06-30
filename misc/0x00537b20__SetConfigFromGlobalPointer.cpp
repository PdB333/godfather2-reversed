// FUNC_NAME: SetConfigFromGlobalPointer
void SetConfigFromGlobalPointer(void)
{
    // Call a function with a global object pointer and a value from another global's offset 4.
    // DAT_0121a390 is likely the main game manager or some manager singleton.
    // DAT_0121b638 is likely a configuration structure, and offset 4 might be a specific parameter.
    FUN_0060b020(g_pGameManager, *(int *)((char *)g_pConfigData + 4));
    return;
}