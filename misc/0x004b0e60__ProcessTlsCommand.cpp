// FUNC_NAME: ProcessTlsCommand
void __fastcall ProcessTlsCommand(uint *command)
{
    int index = command[2];  // +0x8: index or timestamp (must be non-negative)
    
    if (index >= 0) {
        // Access thread-local storage slot (likely a per-thread buffer/log queue)
        TlsGetValue(g_TlsSlotIndex);
        
        // Send the command with type 0x17, using the first element as ID
        WriteToBuffer(command[0], index << 4, 0x17);  // 0x17 = message type (e.g., kMsgTlsCommand)
    }
}