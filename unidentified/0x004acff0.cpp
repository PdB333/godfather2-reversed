// Function address: 0x004acff0
// Role: Thunk that forwards to the global update function (0x004ae6f0). Called extensively across the game engine.
// FUN_004acff0: forwardToGlobalUpdate
void __cdecl forwardToGlobalUpdate(void)
{
    globalUpdate();
}