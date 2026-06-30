// FUNC_NAME: checkActionCommand
// Function address: 0x006eb7b0
// Role: Dispatches or validates a specific action command (0x5d). Returns 0 if parameter is not the expected command ID. Many callers suggest this is part of a command dispatch table.

int checkActionCommand(int param_1, int commandId) {
    // param_1 is unused, likely 'this' or reserved
    if (commandId == 0x5d) {
        // Call into a function that likely returns some global state or performs the action
        return FUN_007cc370();
    }
    return 0;
}