// FUNC_NAME: DebugManager::submitCommand
// Address: 0x006d0250
// This function submits a debug command to the debug manager.
// It retrieves the debug manager singleton, constructs a command structure
// (command=2, size=0x10, parameter=0), and calls the manager's first virtual method.
// The command likely corresponds to a display or initialization command.

void DebugManager::submitCommand(void* param_1) {
    // Get the debug manager singleton (returns pointer to an object with vtable)
    uint32_t** vtablePtr = (uint32_t**)getDebugManager();  // FUN_009c8f80
    // Build command info: command=2, size=0x10, parameter=0
    DebugCommandInfo cmdInfo;
    cmdInfo.command = 2;   // e.g., CMD_DISPLAY or CMD_INIT
    cmdInfo.size = 0x10;   // size of associated data (if any)
    cmdInfo.parameter = 0; // extra parameter
    // Call first virtual function on the debug manager (e.g., processCommand)
    // param_1 is passed as the object pointer (this in __thiscall) but here it's the first arg
    // The virtual function takes two arguments: param_1 (original this) and pointer to cmdInfo
    (*(void (*)(void*, DebugCommandInfo*))(*vtablePtr))(param_1, &cmdInfo);
}