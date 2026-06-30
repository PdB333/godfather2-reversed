// FUNC_NAME: EngineCommandSender::sendCommand
void __thiscall EngineCommandSender::sendCommand(void* this) {
    // Get the global engine function table (returns pointer to pointer to function)
    void** functionTable = getEngineFunctionTable(); // FUN_009c8f80

    // Command structure: commandId, param1, param2
    struct EngineCommand {
        int commandId;   // +0x00
        int param1;      // +0x04
        int param2;      // +0x08
    };

    EngineCommand cmd;
    cmd.commandId = 2;   // e.g., kCommandSetState
    cmd.param1 = 0x10;   // e.g., kStateActive
    cmd.param2 = 0;      // e.g., 0

    // Call the engine command handler via function table
    // The first entry in the table is the command handler function
    void (*commandHandler)(void*, EngineCommand*) = (void (*)(void*, EngineCommand*))(*functionTable);
    commandHandler(this, &cmd);
}