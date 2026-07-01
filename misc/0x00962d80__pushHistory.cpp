//FUNC_NAME: pushHistory
void pushHistory(void)
{
    // Call to generic push function with string "PushHistory", 0, and a global data pointer
    // FUN_005a04a0 is likely a logging/history push function
    // DAT_00d8cdec is a global history context or buffer
    pushToHistory("PushHistory", 0, &g_historyContext, 0);
    return;
}