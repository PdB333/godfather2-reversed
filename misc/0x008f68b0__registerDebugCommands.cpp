// FUNC_NAME: registerDebugCommands
void registerDebugCommands(void)
{
    // Clear existing debug command handlers
    clearCommandHandlers();  // FUN_007f3fa0

    // If debug commands are enabled, register a set of handlers
    if (g_debugCommandsEnabled != '\0')
    {
        // Register four identical handlers (likely different command strings mapping to same function)
        registerCommandHandler(&kCmdHandler1);  // LAB_00801750
        registerCommandHandler(&kCmdHandler1);
        registerCommandHandler(&kCmdHandler1);
        registerCommandHandler(&kCmdHandler1);

        // Other distinct handlers
        registerCommandHandler(&kCmdHandler2);  // LAB_0080ac50
        registerCommandHandler(kFnHandler3);    // FUN_00460d40
        registerCommandHandler(&kHandler4);     // LAB_00460d80
        registerCommandHandler(&kHandler5);     // LAB_00472420
        registerCommandHandler(&kHandler6);     // LAB_0080b6e0
        registerCommandHandler(&kHandler7);     // LAB_00472440
        registerCommandHandler(kDataHandler8);  // DAT_00738310
    }
}