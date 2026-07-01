// FUNC_NAME: sendGameCommand
// Address: 0x008349e0
// Role: Packs three parameters and a command type into a structure and dispatches to command handler.
// The structure layout: [commandType (int), param1 (int), param2 (byte), param3 (int)]
// This likely sends a game event or sets a property on an entity.

void sendGameCommand(int param1, char param2, int param3)
{
    struct CommandData {
        int commandType;   // +0x00
        int param1;        // +0x04
        char param2;       // +0x08
        int param3;        // +0x0C (padding to align)
    };

    CommandData cmd;
    cmd.commandType = 1;   // e.g., kCommandType_SomeAction
    cmd.param1 = param1;
    cmd.param2 = param2;
    cmd.param3 = param3;

    // Dispatch to command processing function (FUN_00834800)
    processCommand(&cmd);
}