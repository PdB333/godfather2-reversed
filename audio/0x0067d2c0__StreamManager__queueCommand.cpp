// FUNC_NAME: StreamManager::queueCommand
// Address: 0x0067d2c0
// Role: Calls a virtual function on a global command dispatcher, passing a command header with type=2, size=0x10, flags=0.
void StreamManager::queueCommand() {
    // Obtain a pointer to a function table (vtable) from a global singleton
    void** vtablePtr = reinterpret_cast<void**>(FUN_009c8f80());

    // Command header structure: type, data size, flags
    struct CommandHeader {
        int type;  // +0x00
        int size;  // +0x04
        int flags; // +0x08
    };
    CommandHeader cmd;
    cmd.type = 2;
    cmd.size = 0x10;
    cmd.flags = 0;

    // Call the first virtual function in the table
    typedef void (*CommandFunc)(void* thisPtr, CommandHeader* cmd);
    CommandFunc func = reinterpret_cast<CommandFunc>(vtablePtr[0]);
    func(this, &cmd);
}