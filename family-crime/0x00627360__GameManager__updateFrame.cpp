// FUNC_NAME: GameManager::updateFrame
// Address: 0x00627360
// Role: Main per-frame update for game systems. Retrieves delta time, performs pre-update, 
//       zero-parameter update, another pre-update, then post-update with delta, and finalizes frame.
void GameManager::updateFrame(void)
{
    float deltaTime = getDeltaTime();          // FUN_00627290: Get frame delta time (seconds)
    processPreUpdate();                        // FUN_00626f80: Pre-frame logic (e.g., input polling)
    processUpdate(0);                          // FUN_00626fd0: Core update with argument (0 = normal update)
    processPreUpdate();                        // FUN_00626f80: Second pre-update pass
    processPostUpdate(deltaTime);              // FUN_00627010: Post-update dependent on delta (physics, animation)
    finalizeFrame();                           // FUN_006270e0: End-of-frame cleanup
}