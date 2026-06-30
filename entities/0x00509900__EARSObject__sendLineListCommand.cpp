// FUNC_NAME: EARSObject::sendLineListCommand

// Structure fields for command parameters
struct CommandParams {
    int commandId;   // +0x00
    int size;        // +0x04
    int flags;       // +0x08
};

// Singleton retrieved via FUN_009c8f80 – assumed to be a command queue.
class CommandQueue {
public:
    // Virtual method at vtable index 0, takes an object handle and command parameters.
    virtual void pushCommand(void* obj, CommandParams* cmd) = 0;
};

// Forward declaration of global getter for the singleton.
CommandQueue* GetCommandQueue(); // FUN_009c8f80

// This is a member function of an EARS object (param_1 = this).
// It issues a command to draw line lists (command ID 2) with a vertex stride of 16.
void EARSObject::sendLineListCommand(void* object)
{
    CommandParams cmd;
    cmd.commandId = 2;      // e.g., D3DPT_LINELIST
    cmd.size     = 0x10;    // stride = 16 bytes per vertex
    cmd.flags    = 0;       // no extra flags

    CommandQueue* queue = GetCommandQueue();
    // Call through vtable; object passed as first argument (this) to the virtual pushCommand.
    queue->pushCommand(object, &cmd);
}