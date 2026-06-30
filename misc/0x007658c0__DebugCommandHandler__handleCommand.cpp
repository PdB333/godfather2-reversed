// FUNC_NAME: DebugCommandHandler::handleCommand
int __thiscall DebugCommandHandler::handleCommand(int *this, int arg2, int arg3, int arg4, int commandId, int arg6)
{
    int vtablePtr;
    bool flag;
    int someObject;
    int position;

    if (commandId == 0x23) {
        // Check bit0 at offset 0x88 from the object pointed to by this[0x17] + 0x21dc
        // this[0x17] is offset 0x5c, then +0x21dc, then +0x88
        flag = (*(unsigned char *)(*(int *)(this[0x17] + 0x21dc) + 0x88)) & 1;
        DebugHelper::setDebugDrawFlag(flag);  // Enable/disable some debug visualization
        return 1;
    }
    if (commandId == 0x24) {
        // Spawn or retrieve a debug object using a distance from this[0x1f] (offset 0x7c)
        vtablePtr = *this;
        someObject = EntityManager::getDebugEntity(1, 1, 0, this[0x1f], 1.0f);  // 0x3f800000 = 1.0f
        // Call virtual method at vtable offset 0x2c (e.g., Entity::activate or spawn)
        (*(void (__thiscall **)(int))(vtablePtr + 0x2c))(someObject);
        return 1;
    }
    if (commandId != 0x25) {
        // Default processing for other commands
        return CommandHandler::processDefault(arg2, arg3, arg4, commandId, arg6);
    }
    // Command 0x25: spawn visual effect based on current game state
    if (GameState::isPlaying()) {
        // No specific effect ID – use generic spawn
        position = 0;
        someObject = CameraManager::getWorldPosition(0, 0);  // Returns a position handle
        VFXManager::spawnVisualEffect(0, 0, someObject, position);  // Default effect
        CameraManager::releasePosition(someObject);
        return 1;
    }
    if (GameState::isPlayerInCrib()) {
        someObject = 0;
        position = CameraManager::getWorldPosition(0, 0);
        VFXManager::spawnVisualEffect(0x8b85f37b, 0, position, someObject);  // Hash for "spawn_crib_effect"
        CameraManager::releasePosition(position);
        return 1;
    }
    // Fallback: spawn a different effect
    someObject = 0;
    position = CameraManager::getWorldPosition(0, 0);
    VFXManager::spawnVisualEffect(0x90621df4, 0, position, someObject);  // Hash for "spawn_default_effect"
    CameraManager::releasePosition(position);
    return 1;
}