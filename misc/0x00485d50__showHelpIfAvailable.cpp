// FUNC_NAME: showHelpIfAvailable
// Address: 0x00485d50 - Checks global flags and shows help/tutorial if condition met

void showHelpIfAvailable(void)
{
    // g_helpAvailable (0x012053cb) and g_helpAlreadyShown (0x010c3692)
    if (g_helpAvailable != '\0' && g_helpAlreadyShown == '\0')
    {
        // Show help screen with parameter 1 (e.g., tutorial index)
        func_showHelpScreen(1);
        // Initialize help system with the global help object
        func_initHelpSystem(&g_helpObject);
    }
    return;
}