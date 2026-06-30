// FUNC_NAME: CommandManager::sendCommand
// Address: 0x00581c20
// Sends a command with two integer parameters to the command processor.
// The command structure is 4 DWORDs: commandId, arg, 0, 0.
// Calls vtable[5] (offset 0x14) on this.

void __thiscall CommandManager::sendCommand(int commandId, int arg) {
    int cmdData[4];                    // 16-byte command buffer
    cmdData[0] = commandId;            // +0x00
    cmdData[1] = arg;                  // +0x04
    cmdData[2] = 0;                    // +0x08
    cmdData[3] = 0;                    // +0x0C

    // Dispatch via vtable slot 5
    ((void (__thiscall *)(CommandManager*, int*))
     (*(void***)this)[5])(this, cmdData);
}