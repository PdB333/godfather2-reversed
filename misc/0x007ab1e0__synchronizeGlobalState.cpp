// FUNC_NAME: synchronizeGlobalState
// Function address: 0x007ab1e0 - Wrapper that calls the global engine tick function.
// Called from multiple manager update routines (NPCManager, PlayerManager, etc.)
// to synchronize global state each frame.
void synchronizeGlobalState(void)
{
    // Forward call to the actual global state update implementation (0x00800a90)
    updateGlobalTick();
}