// FUNC_NAME: CommandSender::sendCommand

#include <cstdint>

struct Command {
    int32_t type;
    int32_t value;
    int32_t flag;
};

// Global function pointer at DAT_01205868
typedef void (*CommandHandler)(CommandSender* obj, Command* cmd);
extern CommandHandler gCommandHandler;

class CommandSender {
public:
    void sendCommand();
};

void CommandSender::sendCommand() {
    Command cmd;
    cmd.type = 2;       // Command ID: e.g., kCmdInit
    cmd.value = 0x10;   // Parameter: e.g., 16 (controller slot?)
    cmd.flag = 0;       // Flags: none
    // Dispatch command through global handler (likely a system-wide message pump)
    gCommandHandler(this, &cmd);
}