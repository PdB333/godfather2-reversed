// FUNC_NAME: GameManager::mainLoopUpdate
// Function address: 0x0067c960
// Role: Main loop iteration - called every frame to update game logic

int __fastcall GameManager::mainLoopUpdate(GameState* gameState)
{
    // Dereference pointer to get vtable/object
    void* obj = gameState->mainLoopObject; // +0x00
    // Retrieve the "GameMainLoop" singleton or central object
    GameMainLoop* mainLoop = (GameMainLoop*)getNamedObject("GameMainLoop");
    // Call virtual method at offset 0x14 (likely update or tick)
    mainLoop->vtable->update(); // +0x14
    // Update other game systems
    updateGameSystems();
    return 1; // indicates successful frame update
}

// Helper: getNamedObject is FUN_00683280
// updateGameSystems is FUN_0067c8b0