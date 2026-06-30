// FUNC_NAME: CommandDispatcher::executeCommand
// Address: 0x005e2280
// Role: Dispatches a command if the flag at offset 0x1744 is set.
//       Retrieves a handler from a global singleton (DAT_01223510)
//       and calls a virtual method (vtable offset 0x98) on it.

uint __thiscall CommandDispatcher::executeCommand(uint commandId)
{
    // Check if command processing is enabled (flag at this+0x1744)
    if (*(byte *)(this + 0x1744) != 0)
    {
        // Get the command handler (likely from a manager)
        uint handler = FUN_005e2150(); // e.g., getCommandHandler()
        if (handler != 0)
        {
            // Call virtual function at vtable offset 0x98 on the global singleton
            // Arguments: (handler+0x1cc, commandId)
            return (**(code **)(*DAT_01223510 + 0x98))(*(uint *)(handler + 0x1cc), commandId);
        }
    }
    // If not enabled or handler unavailable, return failure/0
    return 0;
}