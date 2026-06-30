// FUNC_NAME: GameplayDebugger::processDebugQuery
// Function address: 0x006e4f10
// Role: Queries a debug interface (via vtable at +0x100) with a command hash, then conditionally calls a debug handler.

void GameplayDebugger::processDebugQuery(int unknownPtr)
{
    // +0x100: Pointer to an interface vtable (e.g., IDebugCommandHandler)
    void** interfaceVtable = *(void***)((int)this + 0x100);

    int commandResult = 0;
    // Virtual call at vtable offset +0x10 (index 4). 
    // First argument: hash 0x383225a1 identifying a specific debug command.
    // Second argument: address to receive an integer result.
    bool isActive = ((bool (*)(int, int*))(interfaceVtable[4]))(0x383225a1, &commandResult);

    if (isActive && unknownPtr != 0)
    {
        // unknownPtr is likely a pointer to a debug manager or state table.
        // +0x28c4 is some offset within that structure (debug buffer or array).
        FUN_006e3e50(this, commandResult, unknownPtr + 0x28c4);
    }
}