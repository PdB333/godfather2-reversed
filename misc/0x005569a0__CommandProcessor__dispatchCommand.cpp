// FUNC_NAME: CommandProcessor::dispatchCommand
void __thiscall CommandProcessor::dispatchCommand(void* thisPtr, uint commandFlags, int commandBuffer, undefined4 extraParam)
{
    // Initialize command processing with zero base values
    prepareCommandDispatch(0, 0, extraParam, thisPtr);
    
    // Encode command type into the status field at offset 0x2c
    // Bits [31:30] set to 3 (active/valid flags), bits [29:2] from commandFlags >> 2
    *(uint*)(commandBuffer + 0x2c) = (commandFlags >> 2) | 0xC0000000;
    
    // Flush or reset internal command state
    resetCommandQueue();
    
    // Notify the game subsystem using event ID 0x2001
    postCommandNotification(0x2001, extraParam, 0);
}